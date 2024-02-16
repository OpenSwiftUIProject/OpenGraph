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
        process.executableURL = URL(filePath: try context.tool(named: "zsh").path.string)
        process.arguments = ["AG/update.sh"]
        try process.run()
        process.waitUntilExit()
    }
}
