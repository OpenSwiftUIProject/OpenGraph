//
//  UpdateModuleCommand.swift
//
//
//

import PackagePlugin
import Foundation

@main
struct UpdateModuleCommand: CommandPlugin {
    func performCommand(context: PackagePlugin.PluginContext, arguments: [String]) async throws {
        let process = Process()
        #if os(macOS)
        let path: String = try context.tool(named: "zsh").url.path()
        let url: URL? = if #available(macOS 14, *) {
            URL(filePath: path)
        } else {
            URL(string: "file://\(path)")
        }
        #else
        let path = try context.tool(named: "zsh").path.string
        let url = URL(string: "file://\(path)")
        #endif
        process.executableURL = url
        process.arguments = ["AG/update.sh"]
        try process.run()
        process.waitUntilExit()
    }
}
