# Mario original / primeiro frame em Battlefield — 2026-10-02

Revisão `original-fighter-assets-1`. **Fighter_Create ainda não executado;
nenhum primeiro frame de gameplay foi produzido.** A seleção e a prévia
animada existentes continuam sendo a interface do port.

## Caminho investigado

O diagnóstico `diagnostics/fighter_create_link_entry.c` usa os headers originais,
`plAllocInfo.internal_id = Ft_Kind_Mario` (0) e chama
`Fighter_FirstInitialize_80067A84` seguido de `Fighter_Create`. É somente uma
entrada para o linker, não uma entrada executável publicada. Mario no CSS usa
CKind externo 8; Battlefield usa StKind externo 31 e GrKind interno 36.

A implementação original de Fighter_Create depende de dados comuns, player,
efeitos, costume/partes, animações, câmera, sombra e colisão. Registra os
processos de atualização no GObj antes de Fighter_Spawn. Portanto carregar
um modelo ou instanciar apenas uma struct Fighter não satisfaz esse caminho.

## Alterações que executam na XEX

- `runtime_archive.c`: cache proprietário de arquivos alinhados, validação de
  tamanho, tabelas, nomes, relocações duplicadas e cadeias externas. Rejeita
  arquivos com externs ainda sem resolução. Rejeita plataforma que não seja
  32 bits big endian. Não modifica os assets originais no disco.
- O parser original HSD_ArchiveParse, que já existia no antigo teste Mario,
  agora também reloca PlCo.dat, PlMrNr.dat e GrNBa.dat. A memória permanece viva
  durante o processo para manter os ponteiros do arquivo válidos.
- `runtime_assets_probe.c`: acessa pelos tipos originais ftLoadCommonData,
  ftDataMario, PlyMario5K_Share_joint e coll_data. Verifica endereços internos,
  atributos finitos, posições e referências de todas as linhas do cenário.
- `os_cache.c`: DCStoreRange, DCFlushRange e DCInvalidateRange usam instruções
  Xenon do XDK, cobertura de linhas de 128 bytes e barreira sync. Invalidate
  usa flush+invalidate (dcbf) e preserva bytes sujos vizinhos; não reproduz o
  descarte de cache do dcbi do GameCube. Validação de DMA em console ainda falta.

Nenhuma função ausente foi substituída por stub. Nenhum arquivo da base original
foi editado. Os novos serviços não são uma implementação completa de GX/AX/HSD.

## Verificação e bloqueios

- Compilação Release/Xbox 360/Compat pelo XDK e conversão retail/RGH concluídas.
- Host x86: parser original em fixture de byte order nativo, quatro arquivos
  reais, truncamento/relocação inválida e rejeição de host incompatível.
- Host x86: alinhamento/cobertura/overflow dos intervalos de cache.
- Xenia: probes nativos de cache/arquivos e regressão Training/CSS/SSS passaram.
  A leitura produziu gravity=0.095, walk_max_vel=1.1, 26 vértices e 23 linhas
  em Battlefield. Isso valida dados, não simulação física nem render de Fighter.
- Auditoria convencional do caminho Fighter: 151 símbolos ausentes, zero
  duplicatas. Auditoria completa anterior: 172 símbolos, 355 referências,
  zero duplicatas. As listas incluem dependências de módulos e tabelas estáticas,
  não necessariamente chamadas durante o primeiro frame.

Os logs `fighter-create-link.txt` mostram quem referencia cada ausência.
Há dependências reais em GX (display lists, arrays, atributos, texturas,
iluminação, TEV e cópia), AX/DSP (vozes/mixer/efeitos), VI e inicialização HSD,
além de serviços OS e canais FIO/MCC de diagnóstico. O diagnóstico adicional
por seções de função usa /Gy para distinguir retenção de módulos; seus objetos
nunca são incorporados automaticamente à XEX.

Controle, estado parado, andar, pulo e colisão **ainda não foram integrados ao
Fighter original**. Só poderão ser testados como gameplay após ligação e
inicialização real do player, common data, HSD, Fighter e cenário. A leitura
de coll_data não foi apresentada como execução de mpLib. O teste atual em
Xenia não substitui a validação em Xbox 360 físico.

## Diagnóstico adicional concluído

985/985 módulos anteriormente compiláveis foram recompilados com /Gy. A ligação permaneceu com 151 símbolos ausentes e zero duplicatas; os resultados estão em fighter-create-functions-summary.json e fighter-create-functions-link.txt. Isso não prova que todas as ausências são chamadas no primeiro frame; tabelas de callbacks e dados também retêm referências.

Corrigida a declaração de __OSCurrHeap e OSSetCurrentHeap na camada de headers do port, usando o allocator original já existente. initialize.c original agora compila sem modificação. O inventário passa a 986/987; debug.c continua incompatível com o FILE/va_list do XDK, com diagnóstico de report já implementado em separado. initialize.c não foi ligado ao runtime porque a posse atual do heap está em hsd_memory.c; integrar seu ciclo de heap sem duplicação/reinicialização de memória viva é um bloqueio adicional. Não se resolveu essa diferença com aliases ou stubs.

Distribuição dos 151 símbolos da auditoria por função: GX 65; áudio AI/AX 35; FIO/MCC 18; OS/PAD/stack 12; VI 8; HSD 7; THP 6. Lista agrupada: logs/fighter-create-blocker-groups.json. A XEX final após a correção de headers passou novamente pelo verify-xenia.ps1 -TrainingPreview; log: logs/fighter-assets-xenia-final.txt. O SHA256 da XEX entregue está em logs/RGH-image-sha256.json.
