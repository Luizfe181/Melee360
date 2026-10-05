# Dados e contratos de plataforma

## Assets

DAT/USD contêm tabelas, ponteiros relativos e símbolos. Relocar não significa interpretar corretamente todos os tipos; externs podem iniciar NULL e ser preenchidos depois. O loader atual valida arquivos e inicializa externs segundo a rotina original examinada, inclusive PlLk. Arquivos extraídos são dados de runtime; decomp é código. Ambos são necessários. HPS fornece música ADPCM decodificada no port; bancos SSM/vozes AX são outro caminho. THP/MTH têm serviços próprios; vídeo de intro funcionando não resolve THP original completo.

## ABI e memória

Gekko e Xenon são PowerPC, mas não intercambiáveis: paired singles, MMIO, cache, toolchain/CRT e convenções de build diferem. Layouts 32 bits, bitfields, alinhamento e ponteiros precisam ser verificados. Funções math já traduzidas também exigem validação numérica; identidade do nome não garante resultados idênticos.

Arena OS reservada: 8 MiB. Heap HSD existente: 64 MiB. ARAM adaptada: orçamento separado. RAM física é consultada no Xbox. initialize.c original ainda precisa integrar ownership e cálculos que supõem endereços GameCube. Não reexecutar init/heap em estruturas vivas para conseguir diminuir símbolos.

## GX

Backend atual cobre subconjuntos de transformação, primitivas, cores/UV indexadas, display lists de primitivas, matriz de posição por vértice e alpha compare. Alguns previews usam renderer próprio de assets e shader simplificado. Isso não prova consumo integral dos estados do GX original. TEV completo, lighting/normais, textura/TLUT, indiretas, cópias EFB/XFB e etapas de profundidade continuam bloqueios. Preservar comando FIFO e ordem de atributos; aceitar parâmetros sem afetar render seria stub de comportamento.

## Áudio

HPS -> PCM -> XAudio2 já toca. Delay/Std/Hi/Chorus processam buffers em testes; cadeia diagnóstica Std/Hi/Chorus chega ao XAudio2 com carry de 160 frames/32kHz. Não é o mixer AX original: faltam aquisição/liberação de vozes, endereços, ADPCM loop state, SRC, volumes/envelopes, prioridades, AUX e callbacks. A cadeia diagnóstica não reproduz sends do jogo. Não inferir que SFX/CPU/gameplay rodam porque há música.

## Serviços

OS/PAD/CARD/DVD possuem adaptadores parciais e probes. FIO usa arquivos locais, MCC remoto continua ausente. Preferência progressiva persistida não muda resolução; VIConfigure/Flush/XFB ainda não existem. Boot/menus validados no Xenia não equivalem a validação da nova build no hardware real.
