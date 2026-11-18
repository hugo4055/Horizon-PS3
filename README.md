# Horizon PS3 Test Client

Protótipo inicial de homebrew para **PS3 Slim com HEN 4.92**, escrito em C usando PSL1GHT, Tiny3D e libfont.

## O que existe nesta versão

- Menu de teste gráfico.
- Navegação básica pelo direcional do DualShock 3.
- Opção de sair do programa.
- Estrutura inicial para começar os testes no PS3.

## O que ainda não existe

Este projeto **ainda não é o port do motor Horizon/Minecraft**. O código atual é apenas uma tela de teste independente. Não inclui Minecraft, download/instalação do jogo, carregamento de mundos ou gameplay.

## Compilação

É necessário ter um ambiente Linux com PS3DEV, PSL1GHT, Tiny3D e libfont configurados. Ajuste `PS3DEV`, `PSL1GHT` e `PATH` de acordo com sua instalação:

```sh
export PS3DEV=/path/to/ps3dev
export PSL1GHT="$PS3DEV/ps3sdk"
export PATH="$PS3DEV/bin:$PS3DEV/ppu/bin:$PATH"
make
```

O Makefile é um modelo inicial; nomes de bibliotecas e regras de empacotamento podem variar entre distribuições PSL1GHT.

## Estado

- [x] Código-fonte inicial recebido e colocado no repositório.
- [ ] Compilar com PS3DEV/PSL1GHT.
- [ ] Gerar um PKG válido.
- [ ] Testar no PS3 Slim com HEN 4.92.

**Não há PKG nem EBOOT.ELF pronto nesta versão.** Nenhuma compilação ou teste em hardware foi realizado ainda.
