# Mapa geral do decomp e do port Xbox 360

AnÃ¡lise do checkout local em 2026-10-02. Objetivo: orientar implementaÃ§Ã£o conjunta de dependÃªncias atÃ© uma partida original, evitando confundir compilaÃ§Ã£o com execuÃ§Ã£o.

Este conjunto cobre a arquitetura geral, o inventÃ¡rio de todos os arquivos de cÃ³digo encontrados e os caminhos prioritÃ¡rios examinados. NÃ£o Ã© uma explicaÃ§Ã£o linha a linha das 608 mil linhas, nem afirma compreensÃ£o semÃ¢ntica individual das 23 mil definiÃ§Ãµes aparentes. Nomes/endereÃ§o decompilados, branches condicionais e tabelas de callbacks exigem investigaÃ§Ã£o adicional.

## Como consultar

1. [Arquitetura e subsistemas](arquitetura.md): responsabilidades de todas as Ã¡reas de Melee, HSD e runtime.
2. [Boot e ciclo de uma partida](boot-partida.md): inicializaÃ§Ã£o original e atualizaÃ§Ã£o do Fighter.
3. [Dados, memÃ³ria e contratos de plataforma](dados-plataforma.md): DAT, joints, ABI, GX e Ã¡udio.
4. [Estado real e bloqueios](estado-bloqueios.md): compilado, integrado, diagnosticado e ainda ausente.
5. [Plano para avanÃ§ar](plano-integracao.md): etapas verificÃ¡veis atÃ© Mario/Link e itens.
6. [InventÃ¡rio completo](inventario.md): contagens e dados consultÃ¡veis por arquivo/funÃ§Ã£o.

A fonte de verdade da ausÃªncia atual Ã© logs/fighter-create-mario-link-summary.json e sua lista missing.txt, nÃ£o os nÃºmeros histÃ³ricos dos outros documentos. Estado atual: 113 ausÃªncias, zero duplicatas; Fighter_Create nÃ£o foi executado. NÃ£o hÃ¡ porcentagem global confiÃ¡vel.
