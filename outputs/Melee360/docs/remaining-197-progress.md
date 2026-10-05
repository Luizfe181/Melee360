# Inventário: 201 → 197 símbolos

Foram extraídos sem mudanças os corpos originais GXInitTexObj, GXInitTexObjCI, GXInitTexObjLOD e GXInitTlutObj. As estruturas internas e a tabela de filtros vêm do mesmo arquivo upstream. SET_REG_FIELD mantém a operação de máscara/deslocamento em C portátil; proveniência de cada corpo e arquivo em logs/portable-gx-provenance.json.

Os probes host e Xenia passaram para formatos/dimensões, ponteiro codificado, textura CI/nome de paleta, clamp de LOD/bias e descriptor TLUT. A XEX Release retail foi gerada e o teste CSS retornou ao título. O original permanece sem alterações. Esses objetos ainda usam endereço codificado no formato GameCube; a ponte GXLoadTexObj terá que recuperar o endereço Xbox completo por um registro de buffers, não presumir que os bits truncados formam um ponteiro válido no Xbox. Inicializar descriptor não equivale a carregar textura na GPU.

Auditoria: 197 símbolos ausentes, 510 referências, zero duplicatas. A solicitação de concluir todos os 201 ainda não foi atendida. Nenhum símbolo foi substituído por função vazia para forçar link.

Pendências: GX 81; AI/AX 39; OS/CPU 26; FIO/MCC 18; HSD 13; VI 12; THP 6; PAD 2. A lista completa está em logs/gameplay-compile/link-missing-symbols.txt.

GX exige submissão de vértices, atributos indexados, estado TEV traduzido em shader, textura/paletas, cópias de render target e matrizes consumidas pelo desenho. AX exige vozes com endereços ARAM válidos, DSP ADPCM/resampling/mix/loop e efeitos; não pode ser resolvido apenas com o streamer HPS. OS exige threads/contextos e adaptação de semântica CPU; HSD precisa inicializar esses recursos sem MMIO. THP contém rotinas internas do decoder, e FIO/MCC representam o canal de desenvolvimento EXI inexistente no Xbox, cuja substituição precisa de um transporte definido. Esses comportamentos permanecem pendentes, não simulados como sucesso.
