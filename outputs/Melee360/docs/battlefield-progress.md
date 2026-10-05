# Battlefield e redução das dependências

Build `battlefield-preview-1`, 1 de outubro de 2026. O código upstream e os assets originais foram preservados. Esta revisão acrescenta um teste nativo de um cenário, ainda sem gameplay.

## O que executa

Em VS Mode -> Melee, selecione um personagem com o direcional, confirme com A e pressione START para abrir Battlefield. LB/RB escolhe uma das quatro variantes originais do fundo; B volta à seleção. O personagem escolhido não aparece no cenário: este teste verifica o mapa, não uma partida. BACK encerra a aplicação.

O leitor usa `map_head` de `GrNBa.dat`, com sete grupos de modelos cobertos pelas quatro variantes. Cada composição desenha a estrutura/plataformas, um fundo e a camada de transição. O interpretador FObj original aplica trilhas de juntas, materiais e texturas. Os loops também respeitam a tabela de flags +0x28 usada por `grAnime_801C8138`, além dos flags do AObjDesc. A câmera vem do arquivo original. O port reaproveita texturas e recursos GPU entre atualizações.

**Ainda não são todas as animações/efeitos do cenário.** Trilhas de eventos 0x28–0x2A requerem callbacks de partículas/som/alvos ausentes; são contadas explicitamente como eventos não suportados. O teste registra 2–4 chamadas desse grupo por amostra. A transição automática aleatória entre fundos e seus overlays procedurais ainda não executa o callback original do cenário. LB/RB permite examinar os fundos manualmente. TEV, luzes e transparência continuam parciais; não há colisão, câmera de partida, fighters, áudio ou lógica de combate.

## Conflito powf e módulos

O conflito foi corrigido no header isolado de compilação: as unidades originais do alvo de diagnóstico usam `Melee360OriginalPowf` para a função original e seus chamadores. O XDK/D3D mantém seu próprio símbolo `powf`. O algoritmo original não foi substituído pelo CRT e o checkout não foi editado. Um teste host da implementação original passou em seis casos de domínio positivo/zero; isso não garante precisão idêntica para todos os valores e plataformas.

Os módulos db, ty e vi agora fazem parte do inventário, eliminando dependências que já tinham implementação no decomp. **985 de 987 unidades compilam**; as duas falhas permanecem em debug.c (stdio interno Metrowerks) e initialize.c (heap GameCube). A biblioteca completa permanece isolada e não foi vinculada à XEX. Avisos de ABI continuam, incluindo 52 C4013 e 2042 C4028; objetos compilados ainda exigem validação antes da execução.

O runtime ganhou oito funções C originais adicionais (33 no total): projeções/frustum/ortho, projeções de textura/luz, rotação em radianos e GXProject. Também incorpora PADClamp original, constantes MSL originais, ponte PSMTXInverse/MTXTrans e atanf com assinatura float. Os probes verificam projeções, clamp de controles e as operações matemáticas anteriores. Exportar GXProject não implementa o pipeline GX completo.

## Resultado do link

A auditoria com objetos originais, runtime e XDK, sem /FORCE nem stubs de funções ausentes, registra **279 símbolos pendentes, 710 referências e zero definições duplicadas**. O número caiu de 377 para 279 (redução líquida de 98). Dos 745 nomes da auditoria inicial, 601 já não estão ausentes, 144 permanecem e há 135 dependências novas reveladas pela ampliação.

| Fronteira | Símbolos |
|---|---:|
| GX / renderizador e descritores | 113 |
| Áudio / DSP / ARAM | 45 |
| OS / CPU / cache / depuração | 40 |
| Memory card | 21 |
| Ferramentas host / comunicação GameCube | 18 |
| Inicialização / memória / render HSD | 14 |
| VI / apresentação GameCube | 12 |
| DVD / arquivos assíncronos | 8 |
| THP original | 6 |
| Configuração PAD GameCube | 2 |

A maioria agora pertence à camada de plataforma. Incluir implementações do Dolphin SDK que escrevem em registradores GameCube não as torna funcionais no Xenon. Os próximos passos são um backend GX real com estado/material/TEV, memória/arenas e serviços assíncronos compatíveis, além de áudio e saves. Não foram criadas funções vazias para fazer o linker aceitar cenas que não funcionam.

## Testes e pacote

A build XDK Release/Compat e a conversão retail passaram, sem import de xbdm. Os testes host verificaram 48 amostras de Battlefield, cobrindo quatro variantes e sete grupos, com geometria finita, índices válidos, mudanças nas animações e zero malhas ignoradas. Arquivos truncados e frames negativos foram rejeitados. Os probes host/nativos de matemática e PADClamp passaram.

O teste automatizado Xenia verifica 120 atualizações por variante (480 no total), zero malhas ignoradas, entrada a partir da seleção e retorno à seleção/VS/menu principal. Os logs separam callbacks não suportados. A seleção de seis personagens também passou em regressão. Ainda falta testar esta revisão no Xbox físico; o log não comprova a aparência dos pixels nem 60 fps no console.

Há uma prévia CPU de Battlefield em `logs/battlefield-cpu-preview.png`, obtida da geometria/texturas reais do leitor. É uma renderização offline aproximada, não uma captura do Xenia ou Xbox.

Pacote completo: `package/RGH/Melee360`. SHA256 de default.xex: `1C8BD397999D6A2807AE6D81412FBE6F50ACD72A7A911BA92E8E224B06D1C9CA`.

Reprodução: `compile-gameplay.ps1`; `collect-gameplay-dependencies.ps1`; `audit-gameplay-link.ps1 -WithRuntime`; `verify-powf.ps1`; `verify-portable-math.ps1`; `verify-stage.ps1`; `package-rgh.ps1`; `verify-xenia.ps1 -StagePreview`.

Evidência detalhada: `logs/gameplay-compile/link-missing-symbols.txt`, `link-audit-summary.json`, `remaining-symbol-groups.json`, `summary.json`, `logs/stage-host.txt`, `logs/powf-host.txt`, `logs/xenia-stage-test.log` e manifestos de procedência. Os relatórios anteriores são históricos. A quantidade de objetos compilados não é porcentagem de gameplay funcionando.
