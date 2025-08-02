//
//  Metadata+Debug.swift
//  OpenGraphShims

import Foundation

@_spi(Debug)
extension Metadata {
    public struct Option {
        let maxLevel: Int
        let ignoreStdlib: Bool
        
        public static var `default` = Option(maxLevel: 3, ignoreStdlib: true)
    }
    
    public var layoutDescription: String {
        var result = ""
        _layoutDescription(&result, recursive: false, level: 0)
        return result
    }
    public var recursiveLayoutDescription: String {
        var result = ""
        _layoutDescription(&result, recursive: true, level: 0)
        return result
    }
    
    private func _layoutDescription(
        _ result: inout String,
        recursive: Bool = false,
        level: Int,
        option: Option = .default
    ) {
        func write(_ value: inout String, string: String, level: Int) {
            value.append("\(String(repeating: "\t", count: level))\(string)\n")
        }
        guard level < option.maxLevel else {
            return
        }
        guard !option.ignoreStdlib || !_typeName(type, qualified: true).hasPrefix("Swift.") || kind == .optional else {
            return
        }
        switch kind {
        case .enum:
            write(&result, string: "enum \(type) {", level: level)
            _ = forEachField(options: [.enumerateEnumCases]) { name, offset, type in // anything contains ._4 will work here
                let fieldName = String(cString: name)
                write(&result, string: "case \(fieldName)(\(type)) // offset = \(offset.hex)", level: level+1)
                if recursive {
                    Metadata(type)._layoutDescription(&result, recursive: true, level: level+1)
                }
                return true
            }
            write(&result, string: "}", level: level)
        case .optional:
            _ = forEachField(options: [.enumerateEnumCases]) { name, offset, type in // anything contains ._4 will work here
                let fieldName = String(cString: name)
                write(&result, string: "case \(fieldName)(\(type)) // offset = \(offset.hex)", level: level+1)
                if recursive {
                    Metadata(type)._layoutDescription(&result, recursive: true, level: level+1)
                }
                return true
            }
        case .struct:
            write(&result, string: "struct \(type) {", level: level)
            _ = forEachField(options: []) { name, offset, type in // only [] and [._2] will work here
                let fieldName = String(cString: name)
                write(&result, string: "var \(fieldName): \(type) // offset = \(offset.hex)", level: level+1)
                if recursive {
                    Metadata(type)._layoutDescription(&result, recursive: true, level: level+1)
                }
                return true
            }
            write(&result, string: "}", level: level)
        case .tuple: break
        case .class:
            write(&result, string: "class \(type) {", level: level)
            _ = forEachField(options: [.enumerateClassFields]) { name, offset, type in // anything contains ._1 will work here
                let fieldName = String(cString: name)
                
                write(&result, string: "var \(fieldName): \(type) // offset = \(offset.hex)", level: level+1)
                if recursive {
                    Metadata(type)._layoutDescription(&result, recursive: true, level: level+1)
                }
                return true
            }
            write(&result, string: "}", level: level)
        default: break
        }
    }
}

extension Int {
    fileprivate var hex: String {
        "0x\(String(format:"%X", self))"
    }
}
