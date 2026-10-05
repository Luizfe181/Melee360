# Seleção: original-css-core-1

Esta revisão substitui a navegação própria em grade por uma integração parcial do código original de `mncharsel.c`. A cena completa de seleção ainda não executa: não é o `mnCharSel_CursorThink` completo nem uma partida.

## Código que executa

O gerador `diagnostics/generate_original_css.py` extrai 14 partes do decomp preservado no commit `17697c2d7e46f023f8c7320b75d8cf254ed8e5a4`. A proveniência com linhas e hashes está em `logs/original-css-provenance.json`. Inclui tabela e limites dos retratos, estruturas de cursor/ficha, leitura e cálculo de deslocamento do analógico, ganho de movimento, limites da mão, hit-test, acompanhamento e interpolação da ficha, posicionamento e gravação de CKind no `CSSData.vs.start.players[0]` original. Os tamanhos das estruturas são conferidos em compilação.

`src/original_character_select.c` fornece uma fronteira própria para um jogador. O agendador GObj já integrado chama o menu, que avança esse núcleo a 60 Hz. O analógico move a mão livre; o direcional fornece valores de analógico como alternativa. A solta a ficha; B recupera ou retorna. A escolha passa pelas regiões originais, não por passos numa grade. O renderer desenha a mão e a ficha dos descritores originais de `MnSlChr.usd`. Os modelos continuam em pose estática.

A chamada `atan2f` desses trechos foi isolada como `Melee360CSSAtan2f` e adaptada à função double do CRT do XDK. Isso elimina o erro de link sem duplicar o símbolo matemático do gameplay original. Os corpos extraídos permanecem intactos; a precisão matemática dessa fronteira não é garantida idêntica ao GameCube. O conflito anterior de `powf` permanece resolvido pela fronteira `Melee360OriginalPowf`.

## Verificação

- Build Release XDK e pacote retail RGH gerados, sem import de xbdm.
- Teste host: 25 regiões e CKind, limites, deadzone, movimento, confirmação, persistência da escolha e recuperação da ficha.
- Teste de geometria: 50 estados segurando/soltando a ficha nos 25 retratos, coordenadas finitas e nenhuma malha ignorada do seletor.
- Teste Xenia: probe original CSS aprovado; navegação em seis personagens, confirmação de Fox com CKind 2, recuperação, retorno ao VS e ao título.
- Teste Xenia de Battlefield: quatro fundos com 120 atualizações cada, zero malhas ignoradas, retorno ao seletor e ao VS.
- `logs/css-original-held-cpu.png` é uma prévia aproximada por rasterização CPU; não é captura do console.
- Nova auditoria de todos os objetos de gameplay: 279 símbolos ausentes, 710 referências, zero definições duplicadas. Não gera uma build completa de gameplay.
- Checkout upstream original permanece sem alterações. Assets e DOL não foram modificados.

## Bloqueios

A cena original completa ainda precisa das dependências reais de JObj/GX, textos, áudio, animações e callbacks do seletor. A ponte atual usa um jogador; todos os retratos ficam disponíveis para diagnóstico. CPUs, quatro controles, nomes, roupas, regras, flags de desbloqueio, timers completos e transições originais ainda não estão integrados. Os painéis inferiores ainda não refletem todo o estado de jogador.

Os 279 símbolos pendentes se distribuem em GX (113), áudio/DSP/ARAM (45), OS/CPU/cache/debug (40), CARD (21), FIO/MCC (18), HSD inicialização/memória/render (14), VI (12), DVD (8), THP (6) e configuração PAD (2). O maior bloqueio para executar a cena completa é a camada de gráficos e inicialização HSD. Compilar 985 de 987 unidades não implica que o gameplay esteja funcional.

START após confirmar continua abrindo somente o diagnóstico animado de Battlefield, com LB/RB para quatro fundos e B para voltar. Sem física, combate, áudio ou animações de lutadores. Esta revisão ainda precisa ser validada no Xbox 360 físico.

## Reproduzir

Execute `verify-original-css.ps1`, `verify-css-scene.ps1`, `package-rgh.ps1 -SkipAssetCopy`, `verify-xenia.ps1 -CharacterPreview`, `verify-xenia.ps1 -StagePreview` e `audit-gameplay-link.ps1 -WithRuntime`. O teste automático injeta posições nos retratos para percorrer o roteiro; não demonstra controle físico do analógico. O teste host separado verifica deslocamento real por valores de analógico.

Copie a pasta inteira `package/RGH/Melee360` para HDD/USB e abra `default.xex` pelo Aurora/XeXMenu. Mantenha `data/` e o arquivo da fonte junto da XEX.
