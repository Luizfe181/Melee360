# Backup do código Melee360

Repositório local criado em 5 de outubro de 2026. Guarda o projeto em outputs/Melee360: código C/C++/HLSL, headers de compatibilidade, geradores, scripts de build/testes, documentação, testes e avisos/licenças de terceiros.

## Fora do Git

Pacote RGH e pacotes de teste; assets, vídeos, músicas e saves; imagens de disco/DOL; fontes extraídas e atlas gerado; builds, bibliotecas/objetos/XEX; logs, capturas e caches; arquivos ZIP; work e projeto DolphinDebug. Esses arquivos locais não foram apagados. Bytecode de shaders é regenerado pelos scripts. Os coeficientes binários de terceiros também permanecem locais e fora deste backup.

A base doldecomp/melee fica separada em work/melee-base e não é copiada para o histórico Git deste port. Revision utilizada: 17697c2d7e46f023f8c7320b75d8cf254ed8e5a4. Para reconstruir, restaurar essa base a partir de https://github.com/doldecomp/melee no caminho esperado, instalar/configurar o XDK e preparar os arquivos locais exigidos pelos geradores. O XDK não faz parte deste repositório.

## Reconstrução

Preservar a estrutura outputs/Melee360 e work/melee-base. Os scripts documentam os caminhos e arquivos locais exigidos: build.ps1, compile-gameplay.ps1, generate-hsd-font-includes.ps1, extract-menu-font.ps1 e compilação dos shaders. A biblioteca de gameplay pode precisar ser recompilada para reconstruir do zero; logs de inventário antigos não estão incluídos. Este backup não foi validado como clone limpo autossuficiente.

Os dados originais do jogo devem ser fornecidos localmente. Não restaurar a pasta package a partir deste repositório, pois ela foi excluída deliberadamente.

## Histórico atual

Último incremento: consumidor combinado de posição projetada/posição de câmera, opcional via gx-shared-eye.flag. Report: outputs/Melee360/docs/gx-shared-eye-20261005.md. Mantidos APIs GX, HSD e gameplay; a camada GX inteira ainda não foi reescrita. Renderer publicado não foi substituído nos últimos experimentos.

Os relatórios históricos preservam limites de cada revisão; links absolutos antigos podem exigir adaptação em outra máquina. O HISTORICO_COMPLETO.md não estava presente na pasta transferida e não faz parte deste snapshot.

## Uso

Consultar alterações com git status. Para novos snapshots, revisar git diff e git diff --cached antes de git commit. A .gitignore exclui recursos do jogo e artefatos pesados, mas arquivos novos devem continuar sendo revisados.

Nenhum remoto configurado ou upload realizado. O commit local permite voltar ao código; uma cópia externa/remoto é necessária para manter esse backup fora deste disco.