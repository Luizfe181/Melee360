# Reuso de recursos no seletor e fingerprints de texturas

Correção após relato de quedas gerais de FPS e pausas ao trocar personagem no Xbox físico.

O seletor 2D chamava Melee360TitleClose em cada mudança de hover: destruía shaders/texturas e limpava o cache CPU, mesmo usando o mesmo arquivo MnSlChr.usd. Agora apenas atualiza seleção e força a próxima amostragem, mantendo recursos e caches. Trocas de cena e o diagnóstico 3D continuam com seu ciclo anterior.

O fingerprint dos pixels processados é calculado uma vez na decodificação da textura e armazenado no cache. syncAnimation reutiliza esse valor; texturas não cacheadas continuam com cálculo completo. A chave existente inclui descritores/material/TEV; mudanças desses dados produzem novo conteúdo e novo fingerprint. Isso preserva a detecção de texturas animadas.

Não muda a velocidade de animação ou reduz resolução. Continuam custos de reconstrução de geometria, cópias de pixels e DrawPrimitiveUP. A intro tem decoder separado e não recebe ganho direto dessa correção. Ainda é necessário medir FPS no console; verificação Xenia não é medição de desempenho do Xbox.
