> Registro historico. A build atual e a auditoria mais recente estao em [battlefield-progress.md](battlefield-progress.md).

# Integração do runtime e auditoria de dependências

Revisão `gobj-runtime-1`, 1 de outubro de 2026. O checkout original foi preservado. Ainda não há partida executável.

A XEX agora executa o agendador original `HSD_GObj_RunProcs`, com seis módulos GObj originais e tabelas inicializadas pela camada Xbox. O menu existente é chamado por um processo GObj real. Testes conferem prioridade, pausa, desativação, exclusão durante callback e destruição de userdata. Isso integra objetos lógicos; não ativa o gerenciador completo de cenas nem os callbacks gráficos originais.

Foram incorporadas 25 funções C originais de matrizes/vetores, extraídas com registro de procedência, e pontes para operações paired-single. Os testes numéricos passaram; a precisão não é prometida como idêntica às aproximações do Gekko. O relógio Xbox fornece ticks de 40,5 MHz por contador de desempenho. É tempo monotônico; conversão para calendário GameCube continua pendente. Também foram corrigidas quatro macros, o protótipo PSMTXTrans e rotinas de relatório fatal.

## Compilação e os 745 símbolos

Compilaram 958 de 960 unidades: os 886 módulos de gameplay/menu e 72 de 74 módulos HSD. Os objetos completos continuam numa biblioteca de diagnóstico, fora da XEX. `debug.c` depende de tipos internos de stdio Metrowerks; `initialize.c` depende de `__OSCurrHeap` e inicialização de heap GameCube. O port usa seus próprios serviços de memória e relatórios.

As fontes SIS/debug foram extraídas do main.dol GALE01 1.02, validado por SHA1, sem alterar o arquivo original. Isso permitiu compilar as unidades correspondentes; não significa que todo o renderizador de texto HSD esteja ativo.

A análise lexical dos 745 nomes encontrou candidatos em fontes upstream para 693, no port para 40 e na fronteira plataforma/SDK para 12. Candidato não garante exportação pública, ABI correta ou portabilidade: várias implementações dependem do hardware GameCube.

A auditoria real de link, incluindo os objetos do runtime atual e os novos módulos HSD, termina com **377 símbolos ausentes e 924 referências**. Dos 745 antigos, **497 deixaram de estar ausentes e 248 permanecem**. A ampliação trouxe **129 dependências novas**. Há também **um conflito de definição: powf do Melee versus powf de d3d9.lib**. Esse conflito requer separar o nome da função original dos símbolos do XDK, preservando seus chamadores; não foi ocultado com /FORCE.

A biblioteca isolada registra 868 dependências externas antes dos serviços nativos/CRT/XDK. Esse número mede uma fronteira diferente da auditoria de link de 377. Avisos continuam relevantes: 47 C4013, 1988 C4028 e funções com retornos incompletos. Compilação não comprova ABI nem funcionamento.

Os próximos bloqueios são GX/TEV e ciclo completo JObj/AObj, áudio AX/AI/DSP, ARAM, DVD assíncrono, CARD e VI, além de módulos de cenas ainda fora do inventário. A seleção atual mantém entrada própria e modelos em pose estática; a lógica completa da seleção e a gameplay ainda não executam.

## Verificação e pacote

A build XDK Release/Compat e o empacotamento retail passaram. Os testes host de GObj e matemática passaram. O teste automatizado no Xenia passou pelo boot, probes de GObj/matemática/relógio, 120 apresentações e 120 atualizações de menu pelo agendador original. Carregou Mario, Luigi, Ness, Pikachu, Pichu e Fox, confirmou/cancelou e voltou ao título. O teste de opções também passou, incluindo navegação, persistência e abertura/retorno dos vídeos de arquivo. O teste de animação também completou 120 atualizações no menu principal, VS e título. Mediu aproximadamente 71–79 ms por construção/upload de menu neste teste Xenia e 23 ms no título; ainda exige otimização e não comprova 60 fps no console. A verificação usa logs/probes, sem inspeção visual dos pixels nem teste desta revisão em console físico.

Pacote: `package/RGH/Melee360`, copiar inteiro para HDD/USB e abrir `default.xex` pelo Aurora/XeXMenu.
SHA256 da XEX: `E93B6CDEF0CEF815A8EFAEF56C99740785637E29F407FD6BE35E16D62A353CE2`.

Evidência: `logs/gameplay-compile/summary.json`, `link-audit-summary.json`, `link-comparison.json`, `link-missing-symbols.txt`, `symbol-providers.json`, `logs/portable-mtx-provenance.json`, `logs/hsd-font-provenance.json` e logs da verificação Xenia. Scripts: `compile-gameplay.ps1`, `collect-gameplay-dependencies.ps1`, `audit-gameplay-link.ps1 -WithRuntime`, `verify-gobj.ps1`, `verify-portable-math.ps1` e `verify-xenia.ps1 -CharacterPreview`.

A estimativa funcional anterior de aproximadamente 20% permanece: a contagem de objetos ou símbolos resolvidos não mede a porcentagem de jogo jogável.
