# GX Alpha Compare — 2026-10-02

Implementado GXSetAlphaCompare com os enums originais: NEVER, LESS, EQUAL, LEQUAL, GREATER, NEQUAL, GEQUAL e ALWAYS; duas referências u8; operações AND/OR/XOR/XNOR. A API valida valores e exige chamada fora de GXBegin. O estado é enviado em constantes para um pixel shader dedicado ao backend GX direto; o resultado decide clip/discard do fragmento. Não é um setter sem efeito.

A semântica de comparações/combinação vem de libs/dolphin/src/dolphin/gx/GXTev.c. O shader atual calcula textura * cor e arredonda alpha saturado para o byte mais próximo antes da comparação. Isso atende o backend atual, sem afirmar equivalência bit a bit com a aritmética inteira de TEV ainda não implementada. O shader scene.hlsl usado pelos previews existentes não foi alterado. Não há pipeline TEV completo, normais iluminadas, GXSetZCompLoc ou renderização dos Fighters concluída.

Arquivos: src/gx_direct.cpp, src/gx_direct.hlsl e header compilado src/gx_direct_PS.h; compile-intro-shaders.ps1 recompila também esse shader com fxc XDK ps_2_0. main.cpp executa o probe de alpha apenas com verification.flag, para não depender de consultas de oclusão no boot normal. O backend continua aplicando a API normalmente sem esse flag.

Probe GPU: 24 desenhos cobrem os oito comparadores em alpha=127,128,129 com referência 128. Outros 16 desenhos cobrem todas as quatro combinações booleanas para cada AND/OR/XOR/XNOR. D3D occlusion query verifica pixels presentes ou ausentes; timeout limitado. Estado alpha salvo/restaurado. O primeiro ensaio falhou em NEVER pois a configuração Xenia occlusion_query=fast retornou um resultado em cache. A configuração local explica esse comportamento; verify-xenia.ps1 agora seleciona strict somente no arquivo temporário do teste isolado, sem editar a configuração do emulador do usuário. O ensaio strict inicial de 28 casos passou; versão final amplia para 40 casos.

Build Release/Compat e fxc passaram. Auditoria Mario/Link: 132 -> 131 símbolos ausentes, zero duplicatas. Logs gx-alpha-build-final.txt e gx-alpha-audit.txt. Sem stubs, /FORCE ou alteração da base original. A ausência resolvida identifica a API presente, não a compatibilidade completa de todos os materiais do jogo.

Fighter_Create e partida continuam não executados. IA Link, ECB completo, combate e itens ainda aguardam as dependências restantes. Esta etapa não acrescenta gameplay simulada.

Resultado final: TrainingPreview passou com os 40 casos GPU obrigatorios e percurso Training/CSS/SSS/retorno ao menu. Log gx-alpha-xenia-final.txt. XEX validada copiada para package/RGH/Melee360/default.xex; hash atualizado. Somente Xenia, sem teste no console nesta etapa.
