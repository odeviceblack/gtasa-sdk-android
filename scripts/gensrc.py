#!/usr/bin/env python3
import os
from pathlib import Path

# Determina a raiz do projeto: diretório onde está este script, subindo um nível
SCRIPT_DIR = Path(__file__).resolve().parent
PROJECT_ROOT = SCRIPT_DIR.parent / "gtasa-sdk-android"

# Configurações
SOURCE_DIR = PROJECT_ROOT / "src"
OUTPUT_FILE = PROJECT_ROOT / "cmake" / "sources.cmake"
VARIABLE_NAME = "SRC_FILES"

def find_sources():
    """Encontra recursivamente todos os arquivos .cpp e .h na pasta src."""
    sources = []
    for ext in ["*.cpp", "*.cxx", "*.c"]:
        sources.extend(SOURCE_DIR.rglob(ext))
    # Converte para caminhos relativos à raiz do projeto (formato CMake)
    sources_rel = [str(p.relative_to(PROJECT_ROOT)).replace("\\", "/") for p in sources]
    return sorted(sources_rel)

def write_cmake_file(sources):
    """Escreve o arquivo .cmake com a lista de fontes."""
    OUTPUT_FILE.parent.mkdir(parents=True, exist_ok=True)
    with open(OUTPUT_FILE, "w") as f:
        f.write(f"# Arquivo gerado automaticamente por gensrc.py\n")
        f.write(f"# NÃO EDITE MANUALMENTE\n\n")
        f.write(f"set({VARIABLE_NAME}\n")
        for src in sources:
            f.write(f"    {src}\n")
        f.write(")\n")
    print(f"[OK] {OUTPUT_FILE} gerado com {len(sources)} arquivos.")

if __name__ == "__main__":
    if not SOURCE_DIR.exists():
        print(f"[ERRO] Diretório 'src' não encontrado em {PROJECT_ROOT}")
        exit(1)
    sources = find_sources()
    write_cmake_file(sources)
