# Ballz 🎮

Um clone simples e divertido do jogo **Ballz**, feito em C/C++ utilizando a biblioteca gráfica [Allegro](https://liballeg.org/). O objetivo do jogo é lançar bolas para destruir blocos antes que eles alcancem o fundo da tela.

![Gameplay Screenshot](./screenshot.png) <!-- Substitua por uma imagem real do jogo -->

---

## 📦 Requisitos

Para compilar e rodar o projeto, você precisa ter:

- [Allegro 5](https://liballeg.org/) instalado
- Compilador C/C++ (ex: GCC, MinGW, Clang)
- CMake (opcional, para builds multiplataforma)

---

## 🔧 Instalação

### Linux

```bash
sudo apt-get install liballegro5-dev
git clone https://github.com/seu-usuario/ballz.git
cd ballz
make
./ballz

🎮 Como Jogar
- Clique e arraste para escolher o ângulo do disparo

- Lance as bolas para quebrar os blocos numerados

- A cada rodada, os blocos descem uma linha

- Se um bloco alcançar o fundo da tela, é game over

## 📁 Estrutura do Projeto
```bash

├── ballz
├── def.c
├── def.h
├── estrutura.c
├── estrutura.h
├── jogo.c
├── jogo.h
├── makefile
├── menu.c
├── menu.h
├── print.c
├── print.h
├── resource/
└── Readme.md

```