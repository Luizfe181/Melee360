# RGBA6, GXSetDither e fechamento do link Mario/Link

Implementado GXSetDither com estado efetivamente consumido pelo shader GX. Em RGBA6_Z24, o fragmento aplica Bayer 2x2 ao RGB antes do fog, preserva o alpha nessa etapa e quantiza RGB/alpha para seis bits no armazenamento A8R8G8B8. Em RGB8, dithering nao altera o resultado. Destination alpha, alpha rejection e mascaras de escrita participam do caminho.

Escopo: render target linear A8R8G8B8, D24S8 e sem multisampling. Blending hardware em RGBA6, sRGB e RGBA6 com AA sao recusados explicitamente. Nao e equivalencia completa do EFB GameCube. Os renderers nativos que desenham diretamente via D3D nao recebem automaticamente esse processamento GX.

GXCopyDisp quantiza a cor de clear RGBA6; partial write masks nesse clear nao sao suportadas. GXCopyTex preserva alpha RGBA6 no readback sem filtro vertical (pesos 0/64/0); filtragem de alpha ainda e bloqueada. Essas extensoes de clear/copy nao receberam um novo teste dedicado RGBA6 nesta revisao; os testes anteriores de copy RGB8/RGB565 continuam na suite.

Validacao: 40 readbacks GPU exatos cobrindo as quatro paridades Bayer, RGB8 com dither ligado/desligado, RGB/alpha seis bits, preto/branco, destination alpha, alpha rejection e mascaras RGB/alpha. O verificador exige o marcador desse teste. Training e Sound passaram no Xenia. A primeira regressao AA encontrou erro na restauracao do formato pelo proprio probe: tentava restaurar RGB565 enquanto o target temporario A8 ainda estava ligado. A restauracao foi movida para depois da reposicao dos targets reais; o log da falha foi preservado em logs/gx-rgba6-aa-stage.txt.

As duas auditorias Mario/Link, incluindo HSD main heap, ligaram com zero simbolos ausentes e zero duplicacoes, sem stubs nem /FORCE. Logs: fighter-create-mario-link-summary.json e fighter-create-mario-link-hsd-main-heap-summary.json. O link-only.exe nao foi executado nem empacotado: seu entrypoint diagnostico pula o CRT e nao inicializa a plataforma para executar uma partida.

O inventario publico GX tem outro escopo: 250 APIs, 116 simbolos compilados, duas funcoes inline originais e 132 APIs sem simbolo runtime. Simbolo compilado nao significa API completa; zero ausencias no caminho Fighter nao significa todo GX/AX pronto.

## Proximos bloqueios

Antes de executar Fighter_Create no runtime real, integrar a sequencia original de players, PdPm.dat, lbHeap/lbArchive, caches de fighter/costume e bombeamento de I/O. Fighter_FirstInitialize ja carrega PlCo.dat por Fighter_LoadCommonData; o probe nativo separado dos arquivos nao substitui a inicializacao desses globais originais. A auditoria de link nao valida a ordem de bootstrap, dados ou callbacks.

AX continua parcial: PCM/ADPCM, SRC NONE/linear, vozes continuas e frame callbacks foram testados. FIR de quatro taps, roteamento completo dos buses aux, retorno de efeitos e aplicacao do depop ao audio final ainda precisam implementacao/validacao.

Referencia primaria para a ordem do dithering e sua ativacao somente em RGBA6: https://github.com/dolphin-emu/dolphin/blob/master/Source/Core/VideoCommon/PixelShaderGen.cpp . Implementacao local usa operacoes float e armazenamento expandido por replicacao de bits; nao foi copiado o corpo do shader Dolphin e nao se declara fidelidade bit a bit do hardware original.

A regressao AA corrigida passou: logs/gx-rgba6-aa-stage-recheck.txt. Quatro variantes Battlefield, 120 updates cada, HSD AA/VI/XFB e restauracao do formato original validados; callbacks de eventos de cenario continuam incompletos (4/4/4/2). Este teste e visual, sem gameplay.

Build final: gx-rgba6-final-build.txt; audio final: gx-rgba6-final-sound.txt. Pacote atualizado em package/RGH/Melee360/default.xex, SHA256 D9EBFCB0EA8757F00677F5928F2A1DD06CB9EBBA86FF1CAA986C0AC57672279F. Backup work/default-before-gx-rgba6.xex; manifesto logs/gx-rgba6-package-verification.json. Base original preservada. Nao testado nesta revisao no console real.

Atualizacao posterior: filtro RGB com alpha preservado e clear regional GXCopyTex quantizado passaram em 28 pixels decodificados. Veja bootstrap-runtime-progress.md; as limitacoes descritas acima sao historicas para copy, enquanto blending/AA/sRGB RGBA6 continuam bloqueados.
