#!/usr/bin/env python3
"""
scripts/bundle.py
Concatenates JavaScript modules in dependency order into dist/spider.bundle.js.
Strips ES6 import and export statements so the code runs natively in all browsers
offline (via file://) and over HTTP without requiring an ES module bundler.
"""

import re
import os

BASE_DIR = os.path.dirname(os.path.dirname(os.path.abspath(__file__)))
DIST_DIR = os.path.join(BASE_DIR, "dist")
OUTPUT_FILE = os.path.join(DIST_DIR, "spider.bundle.js")

FILES = [
    "src/engine/Card.js",
    "src/engine/SpiderGame.js",
    "src/engine/AudioService.js",
    "src/ui/VictoryAnimation.js",
    "src/ui/Renderer.js",
    "src/ui/Dialogs.js",
    "src/ui/Interaction.js",
    "src/main.js",
]

def clean_module_code(code: str, filename: str) -> str:
    lines = []
    for line in code.splitlines():
        # Strip import statements
        if re.match(r'^\s*import\s+', line):
            continue
        # Strip export statements but keep declarations
        line = re.sub(r'^\s*export\s+default\s+', '', line)
        line = re.sub(r'^\s*export\s+(const|let|var|class|function)\s+', r'\1 ', line)
        line = re.sub(r'^\s*export\s*\{[^}]*\};?\s*$', '', line)
        lines.append(line)
    
    body = "\n".join(lines)
    return f"  // --- {filename} ---\n{body}\n"

def main():
    os.makedirs(DIST_DIR, exist_ok=True)
    bundle_parts = [
        '(function() {\n  "use strict";\n'
    ]

    for rel_path in FILES:
        full_path = os.path.join(BASE_DIR, rel_path)
        with open(full_path, "r", encoding="utf-8") as f:
            code = f.read()
        bundle_parts.append(clean_module_code(code, rel_path))

    bundle_parts.append("})();\n")

    bundle_content = "\n".join(bundle_parts)
    with open(OUTPUT_FILE, "w", encoding="utf-8") as f:
        f.write(bundle_content)

    print(f"[OK] Successfully built {OUTPUT_FILE} ({len(bundle_content)} bytes)")

if __name__ == "__main__":
    main()
