# Computer Graphics 2D and 3D Operations

Atividade feita por Eduardo Savian, Marcos Fehlauer, Pablos Marques

## Descriptions

### Desenvolvimento 1.1 - Funções Básicas

- O objetivo deste trabalho é observar um pouco do que vimos em 2D e transportar para 3D, com um pouco de pesquisa:

- Pesquisem sobre a matriz de rotação em 3 dimensões, como ela é decomposta nos diferentes ângulos e como é calculada.

- A partir do código em 2 dimensões, crie um cubo, ele vértices de origem e destino), e desenhado na tela a partir de linhas, desenhando somente o wireframe dos componentes. (A posição dos vértices pode ser colocada na mão, não precisa dos cálculos que fizemos para as formas bidimensionais).

- As funções de escala e translação que fizemos em 2D devem ser adaptadas para funcionar com essa forma 3D. (A translação pode receber x, y e z ao invés dos ângulo e deslocamento).

- A função de rotação também deve ser adaptada (podem utilizar a matriz de rotação estudada neste trabalho para aplicar as transformações), utilizando as 3 rotações pelos eixos principais.

- Devem existir eventos de mouse e/ou teclado no programa para aplicar as operações de escala, rotação e translação.

- Não devem ser utilizados os comandos de glTranslate, glRotate ou glScale no trabalho.

- O trabalho pode ser feito em até 3 pessoas. A data de entrega do trabalho é segunda dia 26/03/23, apresentação em sala.

### Desenvolvimento 1.2 - Leitura de Arquivos e Iluminação

- O objetivo deste trabalho é aprimorar o trabalho anterior, adicionando mais funcionalidades ao que foi proposto:
- A função de leitura de arquivo no arquivo de exemplo deve ser expandida, ele deve carregar (além dos vértices e faces) as normais e as texturas.
- Ao carregar um modelo a forma deve ser carregada como faces, renderizando triângulos e não somente as arestas (wireframe). Os vértices devem levar em conta a posição e a normal para a iluminação.
- As operações de rotação, escala e translação no modelo do trabalho anterior ainda devem existir, mas agora podem utilizar as operações feitas ou as operações do openGL (glRotate, glTranslate e glScale)
- Devem existir pelo menos 3 pontos de luz na cena, que devem ter os componentes de difusa, especular e ambiente. E devem poder ser ativadas ou desativadas.
- O trabalho pode ser feito com o mesmo grupo do trabalho anterior. A data de entrega do trabalho é dia 23/04 apresentação em sala.

## Run on Linux

```bash
<package-manager> install freeglut3-dev
```

```bash
make all
```

```bash
./cgt data/<input_file>
```

```bash
make clean
```

```bash
make clean && make && ./cgt data/<input_file>
```

## Keyboard Function

The `keyboard` function handles keyboard input for various transformations and operations in the program. Here's a breakdown of the supported keys and their corresponding actions:

- **w**: Move object up
- **s**: Move object down
- **a**: Move object left
- **d**: Move object right
- **q**: Move object closer
- **e**: Move object farther
- **i**: Rotate object up (around x-axis)
- **k**: Rotate object down (around x-axis)
- **j**: Rotate object left (around y-axis)
- **l**: Rotate object right (around y-axis)
- **u**: Rotate object clockwise (around z-axis)
- **o**: Rotate object counterclockwise (around z-axis)
- **+**: Scale up
- **-**: Scale down
- **1**: Initialize ambient light
- **2**: Initialize diffuse light
- **3**: Initialize specular light
- **z**: Move light source up
- **x**: Move light source down
- **c**: Move light source left
- **v**: Move light source right
- **b**: Move light source closer
- **n**: Move light source farther
- **9**: Reset light position
- **0**: Reset figure position and properties
- **ESC (27)**: Exit the program

Each key press triggers a specific action, such as moving, rotating, scaling, or initializing lighting properties.
