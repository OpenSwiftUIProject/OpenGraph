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
        process.executableURL = try context.tool(named: "zsh").url
        process.arguments = ["AG/update.sh"]
        try process.run()
        process.waitUntilExit()
    }
}
