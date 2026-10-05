param(
    [string]$AssetsRoot = 'C:\Users\luizf\Documents\melee_extraido',
    [string]$XexTool = 'C:\Users\luizf\Documents\XexTool\xextool.exe',
    [switch]$SkipAssetCopy
)
$ErrorActionPreference = 'Stop'
if (!(Test-Path -LiteralPath (Join-Path $AssetsRoot 'PlMr.dat'))) { throw 'AssetsRoot must contain PlMr.dat.' }
if (!(Test-Path -LiteralPath $XexTool)) { throw 'Set XexTool to the installed executable.' }
& (Join-Path $PSScriptRoot 'build.ps1') -Configuration Release -DecompMode Compat
$sourceImage = Join-Path $PSScriptRoot 'build\Release\Compat\default.xex'
$package = Join-Path $PSScriptRoot 'package\RGH\Melee360'
New-Item -ItemType Directory -Force $package | Out-Null
$destinationImage = Join-Path $package 'default.xex'
& (Join-Path $PSScriptRoot 'extract-menu-font.ps1') -Destination (Join-Path $package 'melee360-font.bin')
# Own homebrew image only; preserve development image. Allow HDD/USB media.
& $XexTool -m r -e e -r m -o $destinationImage $sourceImage
if ($LASTEXITCODE -ne 0) { throw 'RGH image conversion failed.' }
$info = & $XexTool -l $destinationImage
if ($LASTEXITCODE -ne 0 -or !($info -match '^\s+Retail\s*$') -or ($info -match 'xbdm\.xex')) {
    throw 'Expected retail format with no xbdm import.'
}
$info | Where-Object { $_ -match 'Retail|Devkit|Original PE Name|Entry Point|Import Libraries|xam.xex|xboxkrnl.exe|xbdm.xex|Hard Disk|USB' } | Set-Content (Join-Path $PSScriptRoot 'logs\RGH-image-info.txt')
$data = Join-Path $package 'data'
New-Item -ItemType Directory -Force $data | Out-Null
if (!$SkipAssetCopy) {
    foreach ($item in Get-ChildItem -LiteralPath $AssetsRoot -Force) {
        Copy-Item -LiteralPath $item.FullName -Destination $data -Recurse -Force
    }
} elseif (!(Test-Path -LiteralPath (Join-Path $data 'PlMr.dat'))) {
    throw 'SkipAssetCopy requires a package containing the assets already.'
}
@'
Melee360 — original-fighter-assets-1, port experimental para Xbox 360 RGH/JTAG.

Copie a pasta Melee360 inteira para HDD/USB e abra default.xex no Aurora/XeXMenu.
Mantenha data/ e melee360-font.bin ao lado da XEX. Não executa a ISO.

Após uma breve tela de diagnóstico, a build deve reproduzir o vídeo original
MvOpen.mth em 4:3, com a faixa original opening.hps via XAudio2. Ao terminar, aparece o titulo com animacoes originais de GmTtAll.usd.
START pula a intro para o título. START/A no título abre o menu. Direcional
seleciona, A confirma, B volta e BACK encerra. B no menu principal retorna
ao título. Esta revisão foi testada no Xenia; falta teste físico no console.

Dez páginas usam malhas, texturas e descrições inglesas originais: principal,
1-P, VS, troféus, opções, dados, Regular Match, Stadium, Special Melee e Records.
Estas dez paginas agora animam fundo, entrada, destaque e loops originais.
O titulo/Press Start usa animacao original. O handler mn_8022DB10
original controla o menu principal por uma ponte limitada. O gerenciador
completo de cenas ainda falta. Telas profundas têm o aviso Tela provisoria
do port: suas configurações/navegação são próprias. PT/EN dessas telas não
traduz as texturas originais. Os vídeos Special Movie e How to Play podem
ser abertos em Data/Archives, sem áudio.
VS Mode -> Melee abre a selecao de teste com 25 icones e retratos
2D originais no painel P1/HMN; P2-P4 fechados em N/A.
Para o diagnostico 3D, crie debug-css-models.flag ao lado de default.xex.
Esse modo opcional usa DViWaitAJ/FigaTree interpretada por FObj.
O fundo da selecao usa o ciclo original de 200 frames.
Analogico/direcional move a mao livre, A solta a ficha, B pega/volta.
Depois de confirmar, START abre Battlefield: teste de animacoes, sem partida.
LB/RB troca quatro variantes de fundo; B retorna a selecao.
Particulas e a transicao automatica dos fundos ainda nao estao integradas.
Movimento, limites, hit-test, ficha e CKind usam trechos originais do CSS.
A cena completa, CPUs, nomes e roupas ainda faltam; nao inicia partida.
Ice Climbers mostra apenas Popo; Samus tem duas malhas ainda ignoradas.
Ainda faltam telas profundas, transicoes completas de saida, camera/fog/shape
animados e o scheduler original completo. Nao e todas as animacoes do jogo.
Menus usam a musica original menu01.hps decodificada de DSP para XAudio2.
O volume Musica em Opcoes/Som controla a voz. Filmes e titulo seguem sem audio.
Battlefield diagnostico toca vl_battle.hps; retorno ao seletor retoma menu01.hps. Ainda nao ha efeitos AX/SSM ou despacho original de musica de partida.
Não há gameplay ou tela original de
formatação. Materiais/iluminação são parciais. Não é o jogo completo.
melee360.log registra leitura, decode e desenho.

Se o vídeo não carregar, as barras de diagnóstico permanecem: a primeira
indica o loop, a segunda o teste de arquivo do Mario e a terceira responde a A.
O pacote não importa xbdm; é homebrew para RGH/JTAG, não para console original.

Revisão: original-fighter-assets-1. Dados nativos de Mario/Battlefield e cache Xenon validados. Fighter_Create e primeiro frame de gameplay ainda pendentes. O menu executa no agendador original GObj.
Estados GX de blend/profundidade/cor/scissor ligados a D3D e fences Xbox.
Alarmes OS cooperativos e API CARD em containers proprios do port.
O fluxo original de save/formatacao ainda nao esta ligado ao menu.
Alocador OSAlloc original integrado ao HSD em arena propria de 64 MiB.
Matrizes/vetores C originais substituem paired-single; clock Xbox adaptado.
Calculo de luz, fog e tamanhos de textura GX originais integrados.
DVD usa indices originais do FST e callbacks adiados para ler data/.
Calendario original integrado ao relogio do Xbox; saves completos pendentes.
As poses 3D opcionais atualizam no maximo 20 vezes/s; timing de partida pendente.
O log registra decode_avg_ms/upload_avg_ms. Ainda não executa uma partida.
Delay AXFX original integrado e testado; ainda nao ligado ao mixer de partidas.
Trofeus: Galeria/Colecao com Daisy e Party Ball; loteria de demonstracao.
Training -> personagens -> START abre selecao original de cenarios.
So Battlefield aceita A. Dados preparados; runtime de partida pendente.
Nao e Training jogavel. No VS, Battlefield e diagnostico sem partida.
This software is based in part on the work of the Independent JPEG Group.
'@ | Set-Content (Join-Path $package 'LEIA-ME.txt')
Get-FileHash -LiteralPath $destinationImage -Algorithm SHA256 | Select-Object Hash | ConvertTo-Json | Set-Content (Join-Path $PSScriptRoot 'logs\RGH-image-sha256.json')
Write-Output "Package ready: $package"
