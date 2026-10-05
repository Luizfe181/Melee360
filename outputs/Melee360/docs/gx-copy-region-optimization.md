# Untile por região nas cópias GX — 2026-10-04

O caminho normal de GXCopyTex agora desfaz o tiling apenas do retângulo solicitado, incluindo a linha acima e a linha abaixo quando existem. O filtro continua usando os mesmos coeficientes, clamping, expansão RGB565 e alfa RGBA6. Readback GPU, espera, encode GX em RAM, flush, clear e uploads continuam reais. Não há pixels substitutos no caminho normal nem mudanças na decomp base.

Nas sombras de Battlefield, a origem é 640×480, enquanto o pedido é 256×256, formato de cópia 0x20. Antes o untile gerava 1228800 bytes lineares por pedido. Agora gera 263168 bytes (256×257×4), cerca de 78,6% menos bytes nesse estágio. A textura temporária do readback ainda tem tamanho completo; portanto não afirmar redução equivalente de transferência GPU ou eliminação de GPU→CPU→GPU.

## Medição e escolha

Cinco testes de 180 frames na mesma XEX, Xenia headless, Mario CPU/Link CPU: referência, recorte, reutilização do buffer, ambos, referência repetida. Contagens de desenhos e amostras CPU iguais.

| Modo | Total ms/frame | Cópia ms/frame | Espera medida ms/frame | Cópia menos espera |
|---|---:|---:|---:|---:|
| Referência | 346,613 | 37,627 | 14,505 | 23,122 |
| Recorte | 341,718 | 28,574 | 14,769 | 13,805 |
| Reutilização | 347,249 | 30,645 | 14,028 | 16,617 |
| Ambos | 344,872 | 25,193 | 13,566 | 11,627 |
| Referência repetida | 335,929 | 32,148 | 8,881 | 23,267 |

A espera medida ocorreu em 345 chamadas, coincidindo com os 345 pedidos de cópia. Subtrair os tempos aninhados indica aproximadamente 40% menos custo não explicado por essa espera na cópia com recorte. É uma aproximação CPU wall time, não tempo GPU.

A variação do frame total entre referências impede reivindicar ganho confiável de FPS: o recorte foi mais rápido que a primeira referência e mais lento que a repetida. A decisão mantém o recorte por reduzir trabalho e memória linear, com validação funcional. Não extrapolar FPS para console ou menus. Reutilização do buffer não apresentou ganho total claro isoladamente e permanece experimental, desativada por padrão.

Na build final, perfil de 180 frames registrou render 337,929, cópia 29,095 e espera 15,270 ms/frame. Esses números não são um novo A/B pareado e não devem ser usados como percentual de melhoria contra builds anteriores.

## Controle e vida dos recursos

Por padrão, recorte está ativo; gx-copy-full-untile.flag reproduz untile completo para diagnóstico. gx-copy-pool.flag habilita a reutilização experimental. Com pool ativo, alterações de dimensões/formato recriam o recurso; fechamento GX libera recurso e buffer. Nenhuma dessas flags é necessária para a configuração publicada.

Os outros modos gx-diag-* continuam exclusivos de profiling e não foram usados nas regressões finais. O shader simples não é o renderer normal. A otimização RGB segue experimental/desativada.

## Validação

A XEX final apresentou 900 frames originais. Lógica idêntica à referência e sete capturas internas/apresentadas pixel a pixel iguais. Training e navegação dos menus passaram. A imagem testada foi publicada; resultado final e hash constam em logs/gx-copy-region-package-verification.json.

Probes de cópia existentes verificam retângulos com origem deslocada, tamanhos não alinhados ao tile, RGB565/RGB5A3/RGBA8, AA, filtro e clamp. A verificação não garante todos os usos futuros do GX. Não foi medido no console físico; áudio AX permanece incompleto.

## Evidências

Comparação: diagnostics/analyze_gx_copy_candidates.py e logs/gx-copy-candidates-analysis.json. Logs gx-copy-candidate-{baseline,region,pool,both,baseline-repeat}.txt. Perfil final: gx-copy-region-final-profile.txt. Regressões: gx-copy-region-match900.txt, gx-copy-region-logic.txt, gx-copy-region-captures.txt, gx-copy-region-training.txt e gx-copy-region-menu.txt. Capturas verificadas por diagnostics/verify_gx_copy_region_render.py.

Próximo trabalho nesse caminho: evitar decode/alocação/upload repetidos de cópias dinâmicas e estudar uma representação GPU nativa preservando a imagem codificada em RAM e suas mutações. O readback completo continua existindo; esta revisão reduz apenas uma parte comprovada do trabalho CPU.


SHA256 publicado: 363C00C0DBF36CB9A88841093D1FB83D5AB06DF8676BD13416C13CB3FFDD5C5A. A imagem anterior está preservada em work/default-before-gx-copy-region-20261004.xex.
