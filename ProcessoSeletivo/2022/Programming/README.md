# Desafios Programação
Nos desafios da programação você pode apresentar a solucão através de fluxogramas, pseudo-linguagem ou alguma linguagem de programação de sua preferência.

#### Descrever lógica para robô seguir a linha
- Levando em consideração a leitura dos sensores frontais do robô, ajustar a velocidade dos motores para que a linha seja seguida. 
Pode-se utilizar técnicas como "bang-bang" ou PID.
- Se achar necessário pode-se utilizar encoders na lógica ou outro dispositivo que julgar adequado.

#### Descrever lógica para parada do robô
Em uma competição o robô pode percorrer a pista mais de uma vez. Isso possibilita o mapeamento da pista na primeira tomada de tempo com base nas marcações que são colocadas nela. Dessa forma, é possível identificar curvas, retas e o momento da parada. Com o intuito de utilizar esses dados para otimizar os parâmetros do robô quando ele percorrer a pista das próximas vezes. Com base nisso desenvolva os algoritmos solicitados abaixo: 
- Considerar o sensor lateral direito para parada do robô, a parada deve ocorrer após a leitura de duas marcações na direita da pista.
- Fique livre para sugerir outras formas de parada do robô, por exemplo, pela leitura de pulsos dos encoders.

#### Leitura de um encoder
Utilizando um encoder e, considerando que ele está acoplado num sistema motor-roda, descreva detalhadamente o algoritmo para converter os pulsos do encoder na velocidade média do motor (RPM) e distância percorrida (m). Considere que a roda possui um raio $R$
- Nesse desafio não é necessário programar, mas deve-se deixar explícito as fórmulas e a matemática por trás da conversão.
- Levar em conta os sinais elétricos enviados pelo encoder para fazer a contagem de pulsos.

Para mais informações sobre encoders acesse [Magnetic Encoder Pololu](https://www.pololu.com/product/1523).

#### [Opcional] Descrever algoritmo para leitura de um botão
Considerando que você está fazendo a leitura de um sinal enviado por um botão, desenvolva um algoritmo que conte a quantidade de vezes que ele foi pressionado.
- Só considere uma nova contagem se o botão for solto e depois pressionado novamente.
- Explique o que é o efeito bouncing em botões.

#### Sugestões
- Para desenvolver fluxogramas pode-se utilizar sites ou programas como [LucidChart](https://lucidchart.com) ou Powerpoint.
- Você pode optar por utilizar uma linguagem de programação ex: C, C++, python, etc. Para essas linguagens existem várias IDEs ou editores de código-fonte que podem ser utilizados, como: Dev C++ ou Code Blocks (C e C++), Anaconda (distribuição para python), VSCode (várias linguagens), notepad++ (várias linguagens), etc.
- Se preferir também pode usar pseudo-linguagem, assim você pode trabalhar com editores de texto (Word, notepad) ou código-fonte (notepad++) para fazer o desafio.
- Além disso, é permitida a resolução à mão do desafio *Leitura de um Encoder*, visto que é necessário apresentar fórmulas.
- Para mais informações sobre seguidores de linha, acesse [Treinamento seguidor de linha](https://github.com/Tamandutech/KnowledgeBase_LineFollower/blob/feature/processo_seletivo_2022/Treinamentos/Geral/LineFollower_Geral.pdf). 
