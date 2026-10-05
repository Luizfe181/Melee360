# Melee360

Port nativo experimental de **Super Smash Bros. Melee para Xbox 360 RGH/JTAG**, baseado no código de [doldecomp/melee](https://github.com/doldecomp/melee).

Este repositório guarda o código, scripts, testes e documentação do port. **Não contém uma build pronta do jogo, pacote RGH, imagens de disco, assets, saves ou o XDK.**

## Estado do projeto

O ambiente de desenvolvimento já executou intro, título e menus com assets originais, seleção parcial de personagens/cenários e uma partida de diagnóstico **Mario CPU × Link CPU em Battlefield**, usando lógica e renderização HSD/GX originais.

| Área | Estado |
| --- | --- |
| Boot e runtime Xbox | `default.xex` gerado pelo XDK; inicialização e serviços integrados em etapas. |
| Intro e título | Reprodução de vídeo/áudio e título animado no ambiente local. |
| Menus e seleção | Assets/animações originais e subconjuntos de código original; cenas profundas e modos ainda parciais. |
| Gameplay | Caminho Mario/Link/Battlefield executado; não representa todos os modos, personagens, itens ou fim de partida. |
| GX → Direct3D/Xenos | Backend experimental com TEV, texturas, transformações e cópias nos modos aceitos; fidelidade/desempenho ainda em revisão. |
| Áudio | HPS, AX/AI/ARAM e XAudio2 com implementações incrementais; há modos e validações pendentes. |
| Plataforma | Adaptadores OS, PAD/XInput, DVD/filesystem e CARD; containers CARD próprios, diferentes de RAW/GCI. |

As auditorias selecionadas de Mario/Link chegaram a zero símbolos pendentes. Isso **não significa que todo o jogo ou todas as APIs GX estejam completos**. Não há uma porcentagem confiável de conclusão.

## Arquitetura

```text
Melee original / HSD
        ↓
API GX e serviços esperados pelo jogo
        ↓
Camada de tradução Melee360
        ↓
Direct3D/Xenos · XAudio2 · XInput · serviços nativos Xbox 360
```

A prioridade é preservar gameplay, física, AI e state machines originais. As adaptações ficam na fronteira da plataforma; os caminhos anteriores são mantidos para comparar comportamento e desempenho.

## Organização

```text
outputs/Melee360/
├── Melee360.sln / Melee360.vcxproj
├── src/             Código do port e shaders HLSL
├── compat/          Headers, fronteiras e código gerado de compatibilidade
├── diagnostics/     Geradores, auditorias e experimentos
├── tests/           Testes host
├── docs/            Relatórios de implementação, testes e limites
└── third_party/     Avisos e licenças de componentes utilizados

work/melee-base/      Checkout original — preparado localmente, fora do Git
```

`build/`, `logs/`, `package/`, capturas, caches e binários são locais e ignorados. Fontes extraídas do jogo e bytecode compilado de shaders também ficam fora do backup; os respectivos geradores/fontes permanecem versionados.

## Preparar o ambiente

O projeto atual utiliza Windows, PowerShell, ferramentas Visual Studio 2010/MSBuild e uma instalação local do Xbox 360 SDK/XDK. Os testes host também utilizam o compilador VS2010 e Windows SDK. Geradores usam Python; os analisadores de capturas usam Pillow. Xenia é usado nos testes de execução.

1. Preserve a estrutura de diretórios acima.
2. Prepare o checkout original na raiz do repositório:

   ```powershell
   New-Item -ItemType Directory -Force work | Out-Null
   git clone https://github.com/doldecomp/melee.git work/melee-base
   git -C work/melee-base checkout 17697c2d7e46f023f8c7320b75d8cf254ed8e5a4
   ```

3. Configure `XEDK` para sua instalação local. Vários scripts também contêm caminhos locais do XDK, Python, VS2010, Xenia e dados do jogo: revise-os para sua máquina.
4. Forneça localmente os arquivos de sua cópia do jogo. Os geradores de fontes/DAT/FST exigem entradas específicas; os offsets de fontes registrados correspondem ao DOL verificado GALE01 1.02.
5. Gere os arquivos ignorados e o inventário/biblioteca de gameplay antes de montar o modo integrado.

**A reconstrução completa a partir de um clone limpo ainda não foi validada.** Este repositório é um backup do desenvolvimento, não um instalador autossuficiente. Coeficientes binários de terceiros usados por geradores de áudio também precisam ser preparados localmente.

## Compilar

Os comandos abaixo são executados em `outputs/Melee360`:

```powershell
# Bring-up mínimo, sem integração do decomp
.\build.ps1 -DecompMode None -Configuration Release

# Compilação/inventário das unidades originais
.\compile-gameplay.ps1

# Build integrada, após preparar dependências e arquivos gerados
.\build.ps1 -DecompMode Compat -Configuration Release
```

O modo `Raw` existe para diagnosticar incompatibilidades com os headers originais; não é o caminho recomendado de build funcional.

A saída integrada Release fica em `build/Release/Compat/default.xex`. `package-rgh.ps1` prepara o pacote local, que permanece fora do Git. Não há artefatos de jogo distribuídos neste repositório.

## Testes e otimizações recentes

Os testes automatizados recentes usam Xenia com áudio silenciado, pacotes separados e restauração da XEX de referência. Ganhos medidos no Xenia não devem ser extrapolados para o console real.

- **Submissão nativa:** novo módulo `gx_native_submit`, opcional via `gx-native-submit.flag`, usando BeginVertices/EndVertices do XDK. Probes e capturas selecionadas coincidiram com o caminho anterior. A tentativa com buffers explícitos falhou no probe de alpha e ficou isolada como experimento.
- **Posição compartilhada:** `gx-shared-eye.flag` evita transformar o mesmo ponto duas vezes para projeção e iluminação. Passou em 1.280 comparações host exatas, probes e capturas dos frames 1/60. Redução observada de 1,5–2,2% no tempo de render em três ensaios de 180 frames; ainda requer validação ampliada.
- **Texturas/cópias:** cache por conteúdo, orçamento de 64 MiB, untile regional e reuso opcional de textura bound têm relatórios próprios. Experimentos sem benefício confiável ficam preservados e não são promovidos automaticamente.

As flags opcionais não ficam ativadas apenas por compilar. Compilação, contagens de símbolos, igualdade em capturas selecionadas e execução no emulador são evidências distintas.

## Documentação

- [Revisão por sistema e arquitetura](outputs/Melee360/docs/port-review-20261004.md)
- [Reestruturação da camada GX](outputs/Melee360/docs/gx-rewrite-20261005.md)
- [Transformação compartilhada: testes e medições](outputs/Melee360/docs/gx-shared-eye-20261005.md)
- [Primeira partida CPU original](outputs/Melee360/docs/original-cpu-match-progress.md)
- [Renderização original da partida](outputs/Melee360/docs/original-match-render-progress.md)
- [Mapa geral do decomp](outputs/Melee360/docs/decomp/README.md)
- [Inventário e limites de símbolos](outputs/Melee360/docs/symbol-completion-plan.md)
- [Todos os relatórios](outputs/Melee360/docs)
- [Escopo do backup](README_BACKUP.md)

Os documentos conservam estados históricos. Relatórios antigos de “Fighter ainda não executado” foram superados pelas etapas seguintes; limites específicos devem ser conferidos na revisão correspondente. Alguns links absolutos e referências a logs locais precisam ser ajustados ao consultar em outra máquina.

## Próximas prioridades

Preparação dos vértices, iluminação e texgen; submissão e lifetime de buffers; coerência de texturas/cópias RAM–GPU; fidelidade GX/TEV; modos de áudio pendentes; integração dos modos de jogo; regressões longas e validação no hardware real.

## Créditos e licenças

Base de decompilação: **doldecomp/melee**. O projeto utiliza código e referências de terceiros com avisos em `third_party`, incluindo Independent JPEG Group e componentes/referências Dolphin. Consulte os avisos de cada componente e a licença da base original; este README não atribui uma licença única nova a todo o conteúdo.

Super Smash Bros. Melee e seus assets pertencem aos respectivos titulares. Os dados do jogo e o SDK proprietário não são distribuídos aqui.