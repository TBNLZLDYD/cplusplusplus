"use strict";
var __createBinding = (this && this.__createBinding) || (Object.create ? (function(o, m, k, k2) {
    if (k2 === undefined) k2 = k;
    var desc = Object.getOwnPropertyDescriptor(m, k);
    if (!desc || ("get" in desc ? !m.__esModule : desc.writable || desc.configurable)) {
      desc = { enumerable: true, get: function() { return m[k]; } };
    }
    Object.defineProperty(o, k2, desc);
}) : (function(o, m, k, k2) {
    if (k2 === undefined) k2 = k;
    o[k2] = m[k];
}));
var __setModuleDefault = (this && this.__setModuleDefault) || (Object.create ? (function(o, v) {
    Object.defineProperty(o, "default", { enumerable: true, value: v });
}) : function(o, v) {
    o["default"] = v;
});
var __importStar = (this && this.__importStar) || function (mod) {
    if (mod && mod.__esModule) return mod;
    var result = {};
    if (mod != null) for (var k in mod) if (k !== "default" && Object.prototype.hasOwnProperty.call(mod, k)) __createBinding(result, mod, k);
    __setModuleDefault(result, mod);
    return result;
};
Object.defineProperty(exports, "__esModule", { value: true });
exports.ConfigManager = void 0;
const vscode = __importStar(require("vscode"));
class ConfigManager {
    static getConfig() {
        const config = vscode.workspace.getConfiguration();
        return {
            cplusplusplus: {
                pluginPath: config.get('cplusplusplus.pluginPath', ''),
                clangPath: config.get('cplusplusplus.clangPath', 'clang++'),
                cmakePath: config.get('cplusplusplus.cmakePath', 'cmake'),
                includePaths: config.get('cplusplusplus.includePaths', []),
                compilerFlags: config.get('cplusplusplus.compilerFlags', []),
                enableSyntaxHighlighting: config.get('cplusplusplus.enableSyntaxHighlighting', true),
                enableCodeSnippets: config.get('cplusplusplus.enableCodeSnippets', true),
                enableHover: config.get('cplusplusplus.enableHover', true),
                enableQuickFix: config.get('cplusplusplus.enableQuickFix', true)
            }
        };
    }
    static validateConfig(config, useCache = true) {
        const cacheKey = JSON.stringify(config);
        // 检查缓存
        if (useCache) {
            const cached = this.configCache.get(cacheKey);
            if (cached && Date.now() - cached.timestamp < this.CACHE_TTL) {
                return cached.valid;
            }
        }
        let valid = true;
        // Validate clang path
        if (!config.cplusplusplus.clangPath || config.cplusplusplus.clangPath.trim() === '') {
            vscode.window.showErrorMessage('C+++: clangPath is required');
            valid = false;
        }
        else {
            if (!this.pathExists(config.cplusplusplus.clangPath)) {
                vscode.window.showWarningMessage(`C+++: clangPath ${config.cplusplusplus.clangPath} does not exist`);
            }
        }
        // Validate plugin path if provided
        if (config.cplusplusplus.pluginPath && !this.pathExists(config.cplusplusplus.pluginPath)) {
            vscode.window.showWarningMessage(`C+++: Plugin path ${config.cplusplusplus.pluginPath} does not exist`);
        }
        // Validate cmake path if provided
        if (config.cplusplusplus.cmakePath && !this.pathExists(config.cplusplusplus.cmakePath)) {
            vscode.window.showWarningMessage(`C+++: CMake path ${config.cplusplusplus.cmakePath} does not exist`);
        }
        // Validate include paths - 添加类型验证和内容验证
        if (!Array.isArray(config.cplusplusplus.includePaths)) {
            vscode.window.showErrorMessage('C+++: includePaths must be an array');
            valid = false;
        }
        else {
            for (const includePath of config.cplusplusplus.includePaths) {
                if (typeof includePath !== 'string' || includePath.trim() === '') {
                    vscode.window.showErrorMessage('C+++: Invalid include path format');
                    valid = false;
                    continue;
                }
                // 检查路径是否包含危险字符
                if (includePath.includes('|') || includePath.includes('&') || includePath.includes(';')) {
                    vscode.window.showErrorMessage(`C+++: Include path contains invalid characters: ${includePath}`);
                    valid = false;
                    continue;
                }
                if (!this.pathExists(includePath)) {
                    vscode.window.showWarningMessage(`C+++: Include path ${includePath} does not exist`);
                }
            }
        }
        // Validate compiler flags - 添加类型验证和内容验证
        if (!Array.isArray(config.cplusplusplus.compilerFlags)) {
            vscode.window.showErrorMessage('C+++: compilerFlags must be an array');
            valid = false;
        }
        else {
            for (const flag of config.cplusplusplus.compilerFlags) {
                if (typeof flag !== 'string' || flag.trim() === '') {
                    vscode.window.showErrorMessage('C+++: Invalid compiler flag format');
                    valid = false;
                    continue;
                }
                // 检查标志是否包含危险字符
                if (flag.includes('|') || flag.includes('&') || flag.includes(';')) {
                    vscode.window.showErrorMessage(`C+++: Compiler flag contains invalid characters: ${flag}`);
                    valid = false;
                }
            }
        }
        // 更新缓存
        this.configCache.set(cacheKey, { config, valid, timestamp: Date.now() });
        return valid;
    }
    static pathExists(path) {
        try {
            const pathModule = require('path');
            const fs = require('fs');
            // 解析路径，防止路径遍历
            const resolvedPath = pathModule.resolve(path);
            // 检查路径是否包含危险字符
            if (resolvedPath.includes('|') || resolvedPath.includes('&') || resolvedPath.includes(';')) {
                console.warn(`C+++: Path contains invalid characters: ${resolvedPath}`);
                return false;
            }
            fs.accessSync(resolvedPath);
            return true;
        }
        catch (_a) {
            return false;
        }
    }
    static onConfigChange(callback) {
        return vscode.workspace.onDidChangeConfiguration(() => {
            const config = this.getConfig();
            if (this.validateConfig(config)) {
                callback(config);
            }
        });
    }
}
exports.ConfigManager = ConfigManager;
ConfigManager.configCache = new Map();
ConfigManager.CACHE_TTL = 5000; // 5秒缓存
//# sourceMappingURL=config.js.map