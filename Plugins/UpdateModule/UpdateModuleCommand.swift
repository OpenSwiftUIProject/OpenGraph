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
        #if compiler(>=6.0) // Skip build on WASI 5.10
        let process = Process()
        process.executableURL = try context.tool(named: "zsh").url
        process.arguments = ["AG/update.sh"]
        try process.run()
        process.waitUntilExit()
        #endif
    }
}
