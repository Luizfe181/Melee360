# Recordes Versus — 2026-10-02

Adicionado visualizador somente leitura em Dados > Recordes > Versus. Esquerda/direita escolhem entre 25 lutadores; cima/baixo escolhem o adversário para consultar KOs. Exibe partidas, vitórias, derrotas, dano causado/recebido, ataques acertados/totais, autodestruições e dano máximo.

Fonte: GmSaveData.x1F2C em gm/types.h, offset 0x6C4, 25 FighterData com stride 0xAC e GmStats em +0x34. Índices seguem SelectableCharacterKind em mn/types.h, incluindo Zelda/Sheik como uma entrada. Não se usa a ordem de retratos do CSS. O parser lê u16/u32 big-endian e preserva dano assinado. Decriptação/checksum continuam com crypt.c original sem alteração.

A interface é provisória com fonte do port. Não é o renderer mndiagram original nem produz novas estatísticas de gameplay. Tempo bruto foi lido mas não é exibido porque sua unidade ainda não foi validada. O GCI original é preservado e usado apenas como snapshot. Sem Fighter_Create, sem stubs novos.

Testes host incluem fixture cifrada pelo HSD_Encrypt original, Mario no índice 8, Ganondorf no índice 24, KOs contra adversários distintos, valor assinado negativo, contadores de 16/32 bits e isolamento do lutador vizinho. Save real, corrupção de checksum, identidade e truncamento continuam cobertos. Logs: fighter-records-host.txt, fighter-records-build.txt e fighter-records-xenia.txt. Validação desta mudança usa Xenia; não foi testada no console físico.
