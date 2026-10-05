# Integração HSD AA — 2026-10-03

O perfil `hsd-aa.flag` conecta o preset original `GXNtsc480ProgAa` ao backend Xbox: EFB RGB565 de 640×242 com MSAA 4x, profundidade Z16 MID representada em D24S8, XFB de 640×480, filtro vertical original e scaler para a saída 1280×720. Sem esse arquivo, permanece o perfil progressivo anterior.

## Código

- `GXCompressZ16` e `GXDecompressZ16` são corpos originais extraídos por `diagnostics/generate_portable_gx.py`; proveniência em `logs/portable-gx-provenance.json`. Também importados os presets AA progressivo/entrelaçado originais. Importar o preset entrelaçado não conclui sua integração.
- `gx_z16.hlsl`: quantização LINEAR/NEAR/MID/FAR, usada pelo renderer GX direto, Z-texture e renderer de cenas. O depth clear usa as funções CPU originais.
- `xfb_xbox.cpp`: alvos AA próprios, tamanhos EFB/XFB separados, resolve explícito das quatro amostras, filtro e escala de cópia originais, duas texturas XFB, callbacks/filas originais HSD e apresentação sincronizada.
- `title_scene.cpp` e `fps_overlay.cpp`: viewports correspondem ao EFB ativo. O início de cada frame restaura os alvos AA antes do StartRender original.
- Shaders recompilados pelo XDK; Release/Compat linka sem `/FORCE` e sem stubs adicionados.

## Validação

249.856 roundtrips CPU Z16; 144 comparações GPU de igualdade de profundidade, nos quatro formatos, para profundidade normal e Z-texture. As 694 verificações TEV continuam passando.

Training passou no Xenia com AA integrado, incluindo seleção original de personagens/mapas e preparação das regras. Battlefield passou nas quatro variantes com 120 atualizações de animação por variante, zero meshes descartados. O diagnóstico ainda informa até quatro callbacks de eventos não implementados; isso não representa gameplay executável.

Evidências: `logs/hsd-aa-training-passed.log`, `logs/hsd-aa-stage-passed.log`, `logs/hsd-aa-reordered-build.txt`. O verificador exige o marcador de 120 cópias originais AA e a conclusão do teste Z16 quando a flag está presente.

Durante a validação, executar a bateria Z16 antes de XAudio2Create produziu espera de 180 s na criação do engine. A build anterior passou como controle. Inicializar o áudio antes dessa bateria permitiu concluir os testes; o motivo interno da espera no Xenia não foi provado. Logs anteriores permanecem em `hsd-aa-instrumented-test.txt` e `hsd-aa-baseline-control.txt`.

Auditorias Mario/Link normal e HSD: 69 símbolos pendentes e zero duplicações; Fighter não linkado, executado ou empacotado. Logs `hsd-aa-fighter-audit.txt` e `hsd-aa-extended-audit.txt`.

## Limites reais

- O GX usa três amostras e posições variáveis em 2×2; o Xenon usa quatro amostras fixas. Este perfil é uma aproximação declarada, não equivalência exata.
- TOPHALF/BOTTOMHALF com offsets de ponteiros XFB e buffer temporário ainda precisam de representação própria; continuam bloqueados, não ignorados.
- HalfAspect e scanout físico 480i no console não estão concluídos nem testados neste turno.
- Training/Battlefield continuam previews e preparação de regras; não houve criação do Fighter original ou início da partida.
- A base `work/melee-base` permanece intacta.

## Pacote publicado

`package/RGH/Melee360/default.xex` atualizado; SHA256 `F78C60B9DE0A447D37F71E6D2B2088E49B233B311DB6AF13B54A321F732DB957`. Backup anterior em `work/default-before-hsd-aa.xex`.

AA é opcional: copie `package/RGH/Melee360/profiles/hsd-aa.flag` para a pasta que contém `default.xex`. Sem a flag na raiz, usa o perfil progressivo anterior. A pasta `profiles` sozinha não ativa AA. Para desativar, mova a flag para fora da pasta do executável.

Opções com AA passaram (`logs/hsd-aa-options-passed.log`): páginas originais, vibração, matriz Mono/Stereo, navegação e retorno ao título. A build nova também passou Training sem AA (`logs/hsd-aa-default-passed.log`). Os testes foram no Xenia; este perfil não foi validado em hardware real.
