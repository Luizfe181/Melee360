# css-portraits-allocator-1

A seleção normal usa os retratos 2D de MnSlChr.usd, com ft_hudindex da tabela CSSIcon original. Os IDs das juntas vêm de mnCharSel_803F0DFC; os frames de estado/cor vêm de mnCharSel_804D50CC/D8. P1 é HMN, P2-P4 são N/A. O renderer agora permite amostrar MOBJ e TOBJ separadamente. O painel azul de diagnóstico deixou de cobrir os painéis originais.

Os modelos 3D só são carregados quando existe debug-css-models.flag ao lado de default.xex. Crie esse arquivo e reinicie para o diagnóstico anterior; remova para voltar aos retratos. O código DViWait/FigaTree/FObj e seus testes foram preservados. Isso continua uma ferramenta de diagnóstico.

Diferenças restantes: nome/P1 são texto da camada do port, elementos de slider/estrelas ainda precisam de ajustes, cabeçalho de regras incompleto. Os 25 personagens permanecem desbloqueados para teste. CPU, quatro jogadores, roupas e desbloqueios do save não foram integrados.

## Memória e símbolos

O OSAlloc.c original agora compila no Xbox e no teste Windows de 32 bits. SHA256 e adaptações estão em logs/os-allocator-provenance.json: includes/assertions, bookkeeping DEBUG original e cast u8* numa operação sobre void*. O algoritmo de listas/divisão/união foi preservado. Verificações estáticas: Cell 20 bytes e HeapDesc 24 bytes.

HSD_MemAlloc/HSD_Free usam esse alocador numa arena própria de 64 MiB; HSD_GetHeap inicializa a arena e retorna seu handle. OSCheckHeap agora verifica as listas originais, substituindo o cálculo de orçamento do adaptador anterior. OSInitAlloc tem estado global e não deve ser reinicializado com alocações vivas. O runtime atual mantém uma arena e ainda não executa os threads originais.

Auditoria integral: **254 → 250 símbolos ausentes**, **zero duplicatas**. Resolvidos: OSAllocFromHeap, OSFreeToHeap, OSCreateHeap, OSDestroyHeap. A biblioteca integral ainda não linka e não está executando gameplay na XEX. Maiores bloqueios: GX/FIFO/display lists, AX/DSP/ARAM, OS/threads/alarmes/contextos, CARD, VI, THP e debug FIO/MCC. Funções vazias não atenderiam ao comportamento exigido.

## Verificação

- verify-allocator.ps1: alinhamento, divisão/união, esgotamento, isolamento e reutilização passaram. Os avisos de falta de espaço e heap destruído são negativos esperados.
- verify-css-scene.ps1: 50 poses nos 25 personagens, coordenadas finitas, zero malhas ignoradas passaram.
- package-rgh.ps1 -SkipAssetCopy: build Release/Compat e conversão retail passaram.
- verify-xenia.ps1 -CharacterPreview: probes, retratos Mario/Ness, confirmação, recuperação da ficha e retorno ao menu/título passaram.
- audit-gameplay-link.ps1 -WithRuntime: 250 pendências, zero duplicatas; link integral continua falhando.

logs/css-original-portraits-cpu.png é uma prévia de CPU, não uma captura do console. Esta revisão ainda não foi testada no Xbox físico. Backup: logs/default-before-css-portraits-allocator-1.xex. Base e assets originais preservados.
