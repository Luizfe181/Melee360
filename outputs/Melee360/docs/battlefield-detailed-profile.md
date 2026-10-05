# Perfil detalhado de Battlefield — 2026-10-04

Build Release/Compat compilada com temporizadores opcionais, sem alterar gameplay, shaders, geometria ou acrescentar sincronizações. Teste Xenia headless: mesma XEX, Mario CPU/Link CPU em Battlefield, 180 frames, referência / detalhado / referência repetida. Amostras CPU e contagens de desenho idênticas nas três execuções. A base original permanece intacta.

| Parte medida | ms/frame na execução detalhada | Escopo |
|---|---:|---|
| Lógica original | 2,782 | Scheduler da partida |
| Render total | 344,680 | CPU wall time, incluindo bloqueios de APIs |
| Montagem de pacotes de vértices | 123,268 | Do fim de GXBegin até entrada de submit; inclui chamadas originais emissoras, atributos, transformação, iluminação e texgen |
| Submissão completa | 50,898 | Pipeline, expansão de primitivas e chamadas de desenho |
| Chamadas DrawPrimitiveUP medidas | 32,747 | Parte da submissão; pode incluir bloqueio, não é tempo interno GPU |
| Upload de textura | 74,176 | Cache, decodificação/alocação quando necessária, sampler e cópia auxiliar |
| Cópia de textura | 37,351 | Readback, espera, untile e filtro |
| BlockUntilIdle medidos | 14,679 | Dentro do GX direct/copy; parte dos tempos acima |
| Filtro CPU da cópia | 9,736 | Parte da cópia, após untile |
| Apresentação | 0,335 | Caminho de apresentação medido pelo diagnóstico |

Média de 25482 vértices originais e 1129 submissões GX por frame. Montagem representa aproximadamente 35,8% do render. A lógica dos bots não explica o baixo FPS neste cenário. A próxima investigação deve decompor montagem em transformações, iluminação e geração de UV e verificar trabalho repetido. Upload permanece outra parcela importante.

## Limites da interpretação

Categorias são aninhadas: DrawPrimitiveUP está dentro de submit; filtro e esperas estão dentro de cópia. Não somar todas as linhas. O saldo não atribuído inclui outros caminhos HSD/GX, decodificação, estados e trabalho não instrumentado. Este perfil não mede separadamente transformação, iluminação e texgen, nem todos os waits de outros arquivos/subsistemas.

Não foram usados timestamps GPU; não é possível concluir o custo interno do shader TEV ou a ocupação GPU com esses números. BlockUntilIdle é espera CPU pelo trabalho anterior. O baixo valor de present não exclui gargalo GPU, pois pode existir bloqueio antes de present.

Tempo total referência: 347,984 ms/frame; detalhado: 347,797; referência repetida: 356,977. Não houve penalidade observável do detalhamento neste pequeno grupo, mas a variação das referências não permite inferir overhead zero. Contadores fora das flags continuam desativados. A execução detalhada foi única; usar estes dados como prioridade de investigação, não benchmark definitivo do console.

## Reprodução

Com a XEX de diagnóstico compilada em work/xenia-test/package:

```powershell
& outputs/Melee360/verify-original-bootstrap.ps1 -Match -Performance -Detailed -TimeoutSeconds 300
```

O script exige Performance/Match, cria e remove gx-profile-detail.flag e as flags do diagnóstico, e encerra apenas o Xenia que iniciou. A análise dos três logs salvos é feita por diagnostics/analyze_gx_detail.py. Resultado: logs/gx-detail-analysis.json. Compilação: logs/gx-detail-build.txt. Logs medidos: gx-detail-baseline.txt, gx-detail-measured.txt e gx-detail-baseline-repeat.txt.

Não foi publicada nova XEX. A imagem instrumentada foi testada em 180 frames, sem regressões longas ou comparação visual nesta revisão; o pacote publicado continua a build cache64 previamente validada. O scratch foi restaurado com a imagem publicada após salvar as evidências. O código de instrumentação permanece no projeto para próximos testes.
