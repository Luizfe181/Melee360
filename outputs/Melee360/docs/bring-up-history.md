# Melee360 — primeiro bring-up (2026-10-01)

## Atualização: allocator e listas HSD

`Compat` agora integra **random.c, list.c e objalloc.c originais**, sem modificações no checkout. A versão anterior continha apenas random.c; os registros abaixo descrevem aquele primeiro marco.

Novos arquivos: `src/hsd_probe.c`, `src/hsd_support.cpp`, `compat/hsd_boundary.h`, `compat/dolphin/os.h` e `compat/dolphin/os/OSAlloc.h`. O header Runtime adaptado foi ampliado com uintptr_t/ssize_t, noreturn e uma verificação real do tamanho 0x2C de HSD_ObjAllocData. Os headers list.h, objalloc.h, memory.h e debug.h usados são os originais.

O allocator original usa uma reserva de 64 KiB alinhada em 32 bytes como armazenamento de apoio, com rejeição real de esgotamento. Objetos liberados voltam à freelist HSD. Blocos de apoio ficam reservados até encerrar o programa; não há implementação geral de HSD_Free ou heap Dolphin. HSD_GetHeap/OSCheckHeap operam sobre essa reserva, e assertions produzem mensagem, DebugBreak e exit. A inicialização GX/video foi evitada por um header forçado apenas em objalloc.c que fornece a única declaração necessária de initialize.h, HSD_GetHeap; essa fronteira é específica deste subconjunto.

O teste verifica RNG, conteúdo e encadeamento de listas, contadores used/free/peak, remoção, reutilização do mesmo objeto e limpeza de campos; também exercita pool fixo, alinhamento de 16 bytes, limite de um objeto e esgotamento após quatro objetos. A versão Xbox executa os testes antes de criar a tela: fundo azul indica sucesso, vermelho indica falha. Assertions interrompem antes da tela. Isso não valida todas as operações HSD ou o ABI completo.

**Verificação:** o mesmo probe passou em executável Windows x86 de 32 bits com compilador VS2010 e os três fontes originais (`logs/hsd-host-test.txt`). A imagem Xbox foi compilada/ligada/gerada, com 7 warnings nos fontes originais objalloc.c (sentinelas -1 convertidas para unsigned e parâmetros low/high não usados), 0 erros. O teste no Windows usa uma implementação de apoio equivalente; não testa CRT, GPU ou ABI Xenon.

O usuário mostrou uma captura do primeiro bring-up no Xenia, com fundo azul e barra verde. Isso comprova apresentação daquele executável no emulador; a captura não comprova animação, BACK, versão Compat nem execução no console físico. **Esta nova imagem com allocator/listas ainda precisa ser executada no Xenia/console.**

Próximos blockers atuais: executar a nova imagem, ampliar os testes de limites de heap, substituir a reserva temporária por gerenciamento de memória com ciclo de vida definido e ampliar os headers de plataforma antes de integrar objetos HSD maiores. Assets em Documents/melee/sys ainda não são usados por esta etapa.

## Registro do primeiro marco (histórico)

## Resultado

Projeto Visual Studio 2010 / Xbox 360 XDK criado e compilado localmente. Existem duas imagens separadas:

- `build/None/default.xex`: runtime CRT do XDK, entrada `VOID __cdecl main()`, Direct3D 9, tela azul-escura com barra verde animada, apresentação sincronizada e leitura XInput de até quatro controles. BACK encerra o loop e libera os objetos gráficos.
- `build/Compat/default.xex`: mesmo programa mais a unidade **original e não modificada** `src/sysdolphin/baselib/random.c`. Um teste na entrada redefine a seed para 1 e verifica as duas primeiras saídas (41 e 51235). Falha deixa o fundo vermelho; resultado também vai para OutputDebugStringA.

**Compilação e geração de imagem foram verificadas; execução, apresentação gráfica e teste HSD no Xbox 360 ainda não foram verificados.** Não houve deploy ou conexão a console. Isto ainda não executa Melee e não inclui assets, renderer GX, áudio, personagens ou menus.

## Ambiente inspecionado

- Windows, `XEDK=C:\Program Files (x86)\Microsoft Xbox 360 SDK`.
- Visual Studio 2010 encontrado em `C:\Program Files (x86)\Microsoft Visual Studio 10.0`.
- Plataforma MSBuild `Xbox 360` instalada em `C:\Program Files (x86)\MSBuild\Microsoft.Cpp\v4.0\Platforms\Xbox 360`.
- Build usa MSBuild .NET Framework v4 em `C:\Windows\Microsoft.NET\Framework\v4.0.30319\MSBuild.exe`, compilador/linker PowerPC do XDK e ImageXex **2.0.21256.0** (versão observada na ferramenta; não inferida como versão de todo o SDK).
- Exemplos locais HeadsetAudio2010.vcxproj e TriangleHLSL.cpp consultados para formato do projeto e parâmetros de apresentação. Não foram copiados ou redistribuídos arquivos do SDK.
- Busca por diretórios com nome Melee em Documents não retornou checkout existente; foi feito clone raso do upstream.

## Base preservada

Origem: https://github.com/doldecomp/melee

Commit: `17697c2d7e46f023f8c7320b75d8cf254ed8e5a4`.

Checkout separado em `../../work/melee-base`, relativamente a este README. `git status --porcelain` foi conferido vazio após a integração. Nenhum fonte original foi copiado ou editado: o projeto referencia `random.c` diretamente desse checkout. `MeleeRoot` pode ser sobrescrito como propriedade MSBuild para usar outro caminho. Não foi tentado construir o DOL original.

## Arquivos criados

- `Melee360.sln`, `Melee360.vcxproj`: solução VS2010 e alvo Debug / Xbox 360; sem etapa automática de deploy.
- `src/main.cpp`: bring-up e pequeno teste de integração.
- `compat/Runtime/platform.h`: **adaptador exclusivo do probe random**, com u32/s32/f32, stddef, inline MSVC e verificações de ponteiro/u32 de 32 bits. Não é uma implementação completa de Runtime/platform.h ou do ABI Dolphin. Só participa de `DecompMode=Compat`.
- `build.ps1`: recompilação reproduzível e logs; falha retorna erro.
- `logs/`: evidência das compilações e do primeiro erro de link; `verification.txt`: tamanho, magic e hash das imagens.

## Reproduzir

Abra `Melee360.sln` no Visual Studio 2010, configuração Debug / Xbox 360, ou execute no PowerShell a partir desta pasta:

```powershell
.\build.ps1 -DecompMode None
.\build.ps1 -DecompMode Raw
.\build.ps1 -DecompMode Compat
```

`Raw` é um diagnóstico que **deve falhar atualmente**: inclui a rotina HSD e os headers originais sem o adaptador. None e Compat geram saídas isoladas em build para evitar confundir imagens. A dependência XDK fica na instalação local via XEDK.

## O que compilou / incompatibilidades observadas

1. **None:** compilação, link e ImageXex passaram, sem warnings/erros no log final.
2. **Raw:** `Runtime/platform.h(4)` falha com C1083 porque o CRT antigo não fornece `stdbool.h`. Esta é a primeira incompatibilidade comprovada; headers seguintes ainda não são validados nesse modo.
3. **Primeiro Compat:** fonte compilou, mas link falhou com HSD_Rand/HSD_RandSeedPtr não resolvidos. Os defaults da plataforma compilavam a unidade `.c` como C++; corrigido com `CompileAsC` explícito, mantendo ABI C no main. Log dessa tentativa preservado.
4. **Compat final:** fonte original compilado como C, link e ImageXex passaram sem warnings/erros. O adaptador evita o grafo completo de headers originais; esse sucesso não prova compatibilidade geral do decomp.
5. Os defaults do XDK inicialmente escolheram nomes/caminhos Melee360.exe/xex. Propriedade `OutputFile`, saída do linker e metadado `ImageXexOutput` foram configurados explicitamente para produzir `default.xex`. Logs finais confirmam o arquivo de entrada correto do ImageXex.

## Próximos blockers e ordem sugerida

1. Executar primeiro None e depois Compat num alvo Xbox 360 compatível com imagens de desenvolvimento do XDK. Verificar barra animada, BACK e mensagens do debugger; registrar falhas de CreateDevice/Present. Imagens Debug do XDK não foram validadas como executáveis de console retail.
2. Criar uma camada de headers Xbox separada e ampliar probes gradualmente: bool/inline, tipos, alinhamento real via MSVC, assertions de layout e headers CRT. Inspecionar sys/types e dependências cmath antes de ampliar o HSD; não substituir o Runtime inteiro pelo adaptador estreito.
3. Próxima unidade candidata: list.c, que introduz objalloc e debug/assert. Definir allocator/assert reais antes de ligá-la; evitar stubs silenciosos que mascarem funcionamento.
4. Auditar ABI Gekko/Xenon, instruções e assembly específicos do GameCube, paired singles, convenções de chamada e precisão de floats. Ambos serem PowerPC não estabelece compatibilidade binária.
5. Só depois ampliar OS/PAD/DVD/CARD e HSD. GX→Xenos/D3D, assets/relocações, áudio DSP/ARAM e THP permanecem trabalhos maiores, ainda não implementados nem testados.

Não há dependência do port melee-pc/Aurora neste bring-up. A integração deliberadamente usa apenas uma unidade HSD pequena da base solicitada.
