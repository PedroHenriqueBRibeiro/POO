[![Review Assignment Due Date](https://classroom.github.com/assets/deadline-readme-button-22041afd0340ce965d47ae6ef1cefeee28c7c493a6346c4f15d667ab976d596c.svg)](https://classroom.github.com/a/Dn046MwY)
# trabalho-poo-template


## Aluno: Pedro Henrique Barbosa Ribeiro
## Matrícula: 2121934GCOM


# cd trabx (trab1, trab2, trab3 ou trab4)
# make
# ./agenda
# Ou apenas make run
# Conferir a pasta gerada 'resultados'



trab1/
├── main.c                 # Ponto de entrada
├── util.h/util.c          # Funções utilitárias
├── datetime.h/datetime.c  # Manipulação de datas/horas
├── appointment.h/appointment.c # Hierarquia de compromissos
├── list.h/list.c          # Lista encadeada genérica
├── sort.h/sort.c          # Algoritmo de ordenação
├── parser.h/parser.c      # Parser de arquivos
├── buckets.h/buckets.c    # Resolução de conflitos
├── comparators.h/comparators.c # Funções de comparação
├── writers.h/writers.c    # Geração de relatórios
├── resultado.h/resultado.c # Processamento de resultados
└── Makefile              # Sistema de build


## Classes e estruturas principais

1. DateTime (datetime.h/datetime.c)
Propósito: Manipulação de datas e horas

Estrutura:

c
typedef struct {
    int y, m, d, h, min;
} DateTime;

## Métodos Principais:

days_in_month() - Calcula dias no mês (com bissextos)

parse_date() - Converte "dd/mm/aaaa" para DateTime

parse_time_into() - Converte "hh:mm" para hora

add_minutes() - Adiciona minutos com ajuste automático

cmp_datetime() - Comparação cronológica

fmt_date()/fmt_time() - Formatação para strings

2. Appointment - Classe Base (appointment.h/appointment.c)
Propósito: Base polimórfica para todos os compromissos

## Estrutura:

typedef struct {
    Tipo tipo;              // T_AULA, T_ORIENT, T_REUNIAO, T_EVENTO, T_PARTICULAR
    int id;                 // ID único (6 dígitos)
    DateTime ini, fim;      // Período do compromisso
    int dur_min;            // Duração em minutos
    int grau_prior;         // Prioridade base
    int adiavel;            // Flag de adiável
    char descricao[128];    // Descrição gerada
    int forced_by;          // ID do vencedor em conflitos
    const AppointmentVTable* vptr; // Tabela virtual
} Appointment;

## Sistema de VTable:


struct AppointmentVTable {
    int  (*factor)(const Appointment*);      // Fator de prioridade
    int  (*is_adiavel)(const Appointment*);  // Verifica se é adiável
    void (*describe)(const Appointment*, char*, size_t); // Gera descrição
    void (*data_full)(const Appointment*, char*, size_t); // Dados completos
};


3. Tipos Específicos de Compromissos

## Aula

typedef struct {
    Appointment base;
    char disciplina[MAX_STR];
    char nivel[MAX_STR];  // Graduação, Especialização, Mestrado
} Aula;

## Orientação

typedef struct {
    Appointment base;
    char aluno[MAX_STR];
    char nivel[MAX_STR];
    char assunto[MAX_STR];
} Orient;

## Reunião

typedef struct {
    Appointment base;
    char assunto[MAX_STR];
} Reuniao;

## Evento

typedef struct {
    Appointment base;
    char nome[MAX_STR];
    char local[MAX_STR];
    int dur_dias;
} Evento;

## Particular

typedef struct {
    Appointment base;
    char motivo[MAX_STR];
    char local[MAX_STR];
} Particular;


4. Lista encadeada genérica (list.h/list.c)

Propósito: Estrutura de dados para armazenamento flexível

## Estrutura:

typedef struct Node {
    void* data;
    struct Node* next;
} Node;
Métodos:

list_push_back() - Insere no final

list_free() - Libera memória com callback

list_len() - Conta elementos

list_to_array() - Converte para vetor


5. Sistema de Ordenação (sort.h/sort.c)

Propósito: Algoritmo de ordenação genérico (Merge Sort)

Métodos:

msort() - Ordenação estável com função de comparação customizável

6. Parser de Arquivos (parser.h/parser.c)
Propósito: Leitura e interpretação dos arquivos de entrada

Métodos Principais:

parse_agenda() - Processa arquivo agenda.txt

parse_aula(), parse_orient(), etc. - Parsers específicos por tipo

parse_id() - Extrai ID dos cabeçalhos

zero_base() - Inicializa estrutura base

7. Sistema de Conflitos (buckets.h/buckets.c)
Propósito: Resolução inteligente de conflitos de agenda

## Estrutura:

typedef struct {
    Appointment** confirmed;  // Compromissos confirmados
    Appointment** delayed;    // Compromissos adiados
    Appointment** canceled;   // Compromissos cancelados
    size_t nconf, ndel, ncanc; // Contadores
} Buckets;

## Métodos Principais:

apply_filter() - Algoritmo principal de resolução de conflitos

overlaps() - Verifica sobreposição de horários

wins_over() - Política de desempate

8. Gerador de Relatórios (writers.h/writers.c)
Propósito: Geração dos arquivos de saída formatados

## Métodos:

write_confirmed() - Relatório de confirmados

write_delayed() - Relatório de adiados

write_canceled() - Relatório de cancelados

write_all() - Relatório completo

9. Sistema de Resultados (resultado.h/resultado.c)
Propósito: Processamento do arquivo posicoes.txt e cálculo final

Métodos:

read_positions() - Lê posições do arquivo

write_result_sum() - Calcula e escreve resultado final

## Funcionalidades Principais

# Leitura e parsing de arquivos de entrada
# Sistema de tipos com polimorfismo
# Resolução automática de conflitos
# Ordenação flexível por múltiplos critérios
# Geração de relatórios formatados
# Tratamento de algarismos romanos para desempate
# Sistema modular e extensível

## Arquivos Gerados

Na pasta resultados/:

relatconfirmados.txt - Compromissos confirmados

relatadiados.txt - Compromissos adiados

relatcancelados.txt - Compromissos cancelados

relatcompromissos.txt - Relatório completo

resultado.txt - Resultado final (se posicoes.txt existir)