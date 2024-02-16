//
//  UpdateModuleCommand.swift
//
//
//  Created by Kyle on 2024/2/16.
//

import PackagePlugin
import Foundation

@main
struct UpdateModuleCommand: CommandPlugin {
    func performCommand(context: PackagePlugin.PluginContext, arguments: [String]) async throws {
        let process = Process()
        
        let path = try context.tool(named: "zsh").path.string
        let url: URL?
        #if os(macOS)
        url = if #available(macOS 14, *) {
            URL(filePath: path)
        } else {
            URL(string: "file://\(path)")
        }
        #else
        url = URL(string: "file://\(path)")
        #endif
        process.executableURL = url
        process.arguments = ["AG/update.sh"]
        try process.run()
        process.waitUntilExit()
    }
}
