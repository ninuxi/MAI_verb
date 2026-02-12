# MAI_verb Windows Release Builder
# Run this in PowerShell

param(
    [string]$Version = "v0.1.1"
)

$ReleaseName = "MAI_verb_${Version}_Windows_x64"
$ErrorActionPreference = "Stop"

Write-Host "🚀 MAI_verb Windows Release Builder" -ForegroundColor Green
Write-Host "Version: $Version"
Write-Host "==================================`n"

# Check if JUCE exists
if (-not (Test-Path "JUCE\CMakeLists.txt")) {
    Write-Host "❌ ERROR: JUCE framework not found!" -ForegroundColor Red
    Write-Host "Please download JUCE first:" -ForegroundColor Yellow
    Write-Host "  git clone https://github.com/juce-framework/JUCE.git JUCE"
    Write-Host "`nOr see BUILD_WINDOWS.md for instructions."
    exit 1
}

Write-Host "🔧 Building plugins..." -ForegroundColor Yellow

# Build using CMake
if (Test-Path "build") {
    Remove-Item -Recurse -Force "build"
}

New-Item -ItemType Directory -Path "build" | Out-Null
Set-Location "build"

# Configure
Write-Host "Configuring with CMake..."
cmake .. -G "Visual Studio 17 2022" -DCMAKE_BUILD_TYPE=Release

# Build
Write-Host "Building Release configuration..."
cmake --build . --config Release

Set-Location ..

# Check if build succeeded
if (-not (Test-Path "build\*VST3*")) {
    Write-Host "❌ Build failed! Check the output above." -ForegroundColor Red
    exit 1
}

Write-Host "`n📦 Creating release package..." -ForegroundColor Yellow

# Create release directory
New-Item -ItemType Directory -Path "releases\$ReleaseName" -Force | Out-Null

# Copy VST3
Write-Host "Copying VST3..."
$vst3Path = Get-ChildItem -Recurse "build" -Filter "*.vst3" -Directory | Select-Object -First 1
if ($vst3Path) {
    Copy-Item -Recurse $vst3Path.FullName "releases\$ReleaseName\"
    Write-Host "✅ VST3 copied"
}

# Copy Standalone
Write-Host "Copying Standalone..."
$standalonePath = Get-ChildItem -Recurse "build" -Filter "*.exe" | Where-Object { $_.Directory.Name -like "*Standalone*" } | Select-Object -First 1
if ($standalonePath) {
    New-Item -ItemType Directory -Path "releases\$ReleaseName\Standalone" -Force | Out-Null
    Copy-Item $standalonePath.FullName "releases\$ReleaseName\Standalone\"
    Write-Host "✅ Standalone copied"
}

# Create installation instructions
@"
═══════════════════════════════════════════════════════
  MAI_verb by Mainenti @ aiforlive
  Professional Algorithmic Reverb - Open Source
═══════════════════════════════════════════════════════

🪟 INSTALLAZIONE WINDOWS

╔═══════════════════════════════════════════════════╗
║  INSTALLAZIONE RAPIDA:                            ║
╚═══════════════════════════════════════════════════╝

1️⃣  Estrai il file ZIP scaricato

2️⃣  Installa il plugin VST3:
    - Copia la cartella "Bricasti M7.vst3" in:
      C:\Program Files\Common Files\VST3\
    
    (Potrebbero essere richiesti permessi amministratore)

3️⃣  Per lo Standalone (opzionale):
    - Esegui "Bricasti M7.exe" dalla cartella Standalone
    - Oppure copia in una cartella a tua scelta

4️⃣  Riavvia la tua DAW (Ableton, FL Studio, Reaper, ecc.)

═══════════════════════════════════════════════════════

📦 FORMATI DISPONIBILI:

✅ VST3       - Per tutte le DAW moderne
✅ Standalone - Applicazione indipendente

═══════════════════════════════════════════════════════

🔧 POSIZIONI ALTERNATIVE:

Se non hai permessi amministratore:
  C:\Users\[TuoNome]\AppData\Local\Programs\Common\VST3\

═══════════════════════════════════════════════════════

🔧 RISOLUZIONE PROBLEMI

Problema: Windows SmartScreen blocca il plugin

Soluzione:
  1. Click destro sul file
  2. Proprietà → Spunta "Sblocca" → Applica
  3. Oppure: Click "Maggiori informazioni" → "Esegui comunque"

Problema: Plugin non appare nella DAW

Soluzione:
  1. Verifica il percorso di installazione
  2. Forza il rescan dei plugin nella DAW
  3. Controlla i log della DAW per errori

Problema: Errore VCRUNTIME140.dll

Soluzione:
  Installa Microsoft Visual C++ Redistributable:
  https://aka.ms/vs/17/release/vc_redist.x64.exe

═══════════════════════════════════════════════════════

📄 LICENZA: Open Source (vedi LICENSE nel repository)
🔗 GitHub: https://github.com/ninuxi/MAI_verb
💬 Issues: https://github.com/ninuxi/MAI_verb/issues
👤 Autore: Mainenti @ aiforlive

═══════════════════════════════════════════════════════
"@ | Out-File -FilePath "releases\$ReleaseName\INSTALLATION.txt" -Encoding UTF8

# Create ZIP
Write-Host "`nCreating ZIP archive..."
Compress-Archive -Path "releases\$ReleaseName" -DestinationPath "releases\${ReleaseName}.zip" -Force

Write-Host "`n✅ Release Windows pronta!" -ForegroundColor Green
Write-Host "   📁 releases\${ReleaseName}.zip" -ForegroundColor Cyan

Write-Host "`n📤 Prossimi passi:" -ForegroundColor Yellow
Write-Host "1. Testa il plugin in una DAW"
Write-Host "2. Carica su GitHub Release"
Write-Host "3. Aggiorna README.md con il link"
