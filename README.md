[![Review Assignment Due Date](https://classroom.github.com/assets/deadline-readme-button-22041afd0340ce965d47ae6ef1cefeee28c7c493a6346c4f15d667ab976d596c.svg)](https://classroom.github.com/a/Dn046MwY)

# trabalho-poo-template

## Aluno: Pedro Henrique Barbosa Ribeiro  
## Matrícula: 2121934GCOM

# Como usar

- cd trabx (trab1, trab2, trab3 ou trab4)  
- make  
- ./agenda
- Ou apenas make run
- Conferir a pasta gerada 'resultados'
- make clean
- Para testar outros exemplos, copiar e colar dentro de trabx/agenda.txt e trabx/posicoes/txt os exemplos disponíveis de agenda e posicoes em exemplo02 ou exemplo03.


## Estrutura dos Trabalhos

### TRAB1 (C) e TRAB2 (C++)

#### trab1/
├── main.c # Ponto de entrada
├── util.h/util.c # Funções utilitárias
├── datetime.h/datetime.c # Manipulação de datas/horas
├── appointment.h/appointment.c # Hierarquia de compromissos
├── list.h/list.c # Lista encadeada genérica
├── sort.h/sort.c # Algoritmo de ordenação
├── parser.h/parser.c # Parser de arquivos
├── buckets.h/buckets.c # Resolução de conflitos
├── comparators.h/comparators.c # Funções de comparação
├── writers.h/writers.c # Geração de relatórios
├── resultado.h/resultado.c # Processamento de resultados
└── Makefile # Sistema de build

#### trab2/
├── main.cpp # Ponto de entrada
├── utils.h/utils.cpp # Funções utilitárias
├── datetime.h/datetime.cpp # Manipulação de datas/horas
├── appointments.h/appointments.cpp # Hierarquia de compromissos (OO)
├── linked_list.h/linked_list.cpp # Lista encadeada
├── sorting.h/sorting.cpp # Algoritmo de ordenação
├── agenda_parser.h/agenda_parser.cpp # Parser de arquivos
├── scheduler.h/scheduler.cpp # Resolução de conflitos
├── comparators.h/comparators.cpp # Funções de comparação
├── file_writer.h/file_writer.cpp # Geração de relatórios
├── result_calculator.h/result_calculator.cpp # Processamento de resultados
└── Makefile # Sistema de build


## Classes e Estruturas Principais

### 1. DateTime (datetime.h/datetime.c)

**Propósito:** Manipulação de datas e horas  

**Estrutura:**
typedef struct {
int y, m, d, h, min;
} DateTime;

**Métodos Principais:**  
- `days_in_month()` - Calcula dias no mês (considera bissextos)  
- `parse_date()` - Converte string "dd/mm/aaaa" para DateTime  
- `parse_time_into()` - Converte "hh:mm" para hora  
- `add_minutes()` - Adiciona minutos com ajuste automático  
- `cmp_datetime()` - Comparação cronológica  
- `fmt_date()` / `fmt_time()` - Formatação para strings  



### 2. Appointment - Classe Base (appointment.h/appointment.c)

**Propósito:** Base polimórfica para todos os compromissos  

**Estrutura:**
typedef struct {
Tipo tipo; // T_AULA, T_ORIENT, T_REUNIAO, T_EVENTO, T_PARTICULAR
int id; // ID único (6 dígitos)
DateTime ini, fim; // Período do compromisso
int dur_min; // Duração em minutos
int grau_prior; // Prioridade base
int adiavel; // Flag de adiável
char descricao; // Descrição gerada
int forced_by; // ID do vencedor em conflitos
const AppointmentVTable* vptr; // Tabela virtual
} Appointment;


**Sistema de VTable:**
struct AppointmentVTable {
int (factor)(const Appointment); // Fator de prioridade
int (is_adiavel)(const Appointment); // Verifica se é adiável
void (describe)(const Appointment, char*, size_t); // Gera descrição
void (data_full)(const Appointment, char*, size_t); // Dados completos
};



### 3. Tipos Específicos de Compromissos

- **Aula**
typedef struct {
Appointment base;
char disciplina[MAX_STR];
char nivel[MAX_STR]; // Graduação, Especialização, Mestrado
} Aula;


- **Orientação**
typedef struct {
Appointment base;
char aluno[MAX_STR];
char nivel[MAX_STR];
char assunto[MAX_STR];
} Orient;

- **Reunião**
typedef struct {
Appointment base;
char assunto[MAX_STR];
} Reuniao;


- **Evento**
typedef struct {
Appointment base;
char nome[MAX_STR];
char local[MAX_STR];
int dur_dias;
} Evento;


- **Particular**
typedef struct {
Appointment base;
char motivo[MAX_STR];
char local[MAX_STR];
} Particular;



### 4. Lista Encadeada Genérica (list.h/list.c)

**Propósito:** Estrutura de dados para armazenamento flexível  

**Estrutura:**
typedef struct Node {
void* data;
struct Node* next;
} Node;

**Métodos:**  
- `list_push_back()` - Insere no final  
- `list_free()` - Libera memória com callback  
- `list_len()` - Conta elementos  
- `list_to_array()` - Converte para vetor  


### 5. Sistema de Ordenação (sort.h/sort.c)

**Propósito:** Algoritmo de ordenação genérico (Merge Sort)  

**Método:**  
- `msort()` - Ordenação estável com função de comparação customizável  

### 6. Parser de Arquivos (parser.h/parser.c)

**Propósito:** Leitura e interpretação dos arquivos de entrada  

**Métodos Principais:**  
- `parse_agenda()` - Processa arquivo agenda.txt  
- `parse_aula()`, `parse_orient()`, etc. - Parsers específicos por tipo  
- `parse_id()` - Extrai ID dos cabeçalhos  
- `zero_base()` - Inicializa estrutura base  



### 7. Sistema de Conflitos (buckets.h/buckets.c)

**Propósito:** Resolução inteligente de conflitos de agenda  

**Estrutura:**
typedef struct {
Appointment** confirmed; // Compromissos confirmados
Appointment** delayed; // Compromissos adiados
Appointment** canceled; // Compromissos cancelados
size_t nconf, ndel, ncanc; // Contadores
} Buckets;


**Métodos Principais:**  
- `apply_filter()` - Algoritmo principal de resolução de conflitos  
- `overlaps()` - Verifica sobreposição de horários  
- `wins_over()` - Política de desempate  



### 8. Gerador de Relatórios (writers.h/writers.c)

**Propósito:** Geração dos arquivos de saída formatados  

**Métodos:**  
- `write_confirmed()` - Relatório de confirmados  
- `write_delayed()` - Relatório de adiados  
- `write_canceled()` - Relatório de cancelados  
- `write_all()` - Relatório completo  


### 9. Sistema de Resultados (resultado.h/resultado.c)

**Propósito:** Processamento do arquivo posicoes.txt e cálculo final  

**Métodos:**  
- `read_positions()` - Lê posições do arquivo  
- `write_result_sum()` - Calcula e escreve resultado final  


## Funcionalidades Principais

- Leitura e parsing de arquivos de entrada  
- Sistema de tipos com polimorfismo  
- Resolução automática de conflitos  
- Ordenação flexível com múltiplos critérios  
- Geração de relatórios formatados  
- Tratamento de algarismos romanos para desempate  
- Sistema modular e extensível  



## Arquivos Gerados (pasta resultados/)

- `relatconfirmados.txt` - Compromissos confirmados  
- `relatadiados.txt` - Compromissos adiados  
- `relatcancelados.txt` - Compromissos cancelados  
- `relatcompromissos.txt` - Relatório completo  
- `resultado.txt` - Resultado final (caso `posicoes.txt` exista)



## TRAB2 (C++)

### Estrutura de arquivos
trab2/
├── main.cpp # Ponto de entrada
├── utils.h/utils.cpp # Funções utilitárias
├── datetime.h/datetime.cpp # Manipulação de datas/horas
├── appointments.h/appointments.cpp # Hierarquia de compromissos (OO)
├── linked_list.h/linked_list.cpp # Lista encadeada
├── sorting.h/sorting.cpp # Algoritmo de ordenação
├── agenda_parser.h/agenda_parser.cpp # Parser de arquivos
├── scheduler.h/scheduler.cpp # Resolução de conflitos
├── comparators.h/comparators.cpp # Funções de comparação
├── file_writer.h/file_writer.cpp # Geração de relatórios
├── result_calculator.h/result_calculator.cpp # Processamento de resultados
└── Makefile # Sistema de build



### Classes e Estruturas Principais

#### 1. DateTime (datetime.h/datetime.cpp)

**Propósito:** Manipulação de datas e horas (versão C mantida)  

**Estrutura:**
struct DateTime {
int y = 0, m = 0, d = 0, h = 0, min = 0;
};


**Métodos Principais:**  
- `days_in_month()` - Dias no mês (considera bissextos)  
- `parse_date()` - Converte "dd/mm/aaaa" para DateTime  
- `parse_time_into()` - Converte "hh:mm" para hora  
- `add_minutes()` - Adiciona minutos com ajuste automático  
- `cmp_datetime()` - Comparação cronológica  
- `fmt_date()` / `fmt_time()` - Formatação para strings  


#### 2. Sistema de Tipos com Herança e Polimorfismo (appointments.h/appointments.cpp)

**Enumeração de Tipos:**
enum class Tipo { AULA = 0, ORIENT = 1, REUNIAO = 2, EVENTO = 3, PARTICULAR = 4 };

**Funções Auxiliares:**  
- `base_factor()` - Retorna fator base por tipo  
- `tipo_rank_for_tiebreak()` - Ranking para desempate  

**Classe Base Appointment:**
class Appointment {
public:
Tipo tipo;
int id = 0;
DateTime ini{}, fim{};
int dur_min = 0;
int grau_prior = 0;
bool adiavel = false;
std::string descricao;
int forced_by = -1;


virtual ~Appointment() = default;
virtual int factor() const = 0;           
virtual bool isAdiavel() const = 0;       
virtual void describe() = 0;              
virtual void dataFull(std::string& out) const = 0; 

int priority() const { return grau_prior * factor(); } 
};



#### Classes Derivadas

- **Aula**
class Aula : public Appointment {
std::string disciplina, nivel;
// factor() = 2, não adiável
};


- **Orientação**
class Orient : public Appointment {
std::string aluno, nivel, assunto;
// factor() = base_factor + 1 se não adiável
};


- **Reunião**
class Reuniao : public Appointment {
std::string assunto;
// factor() = base_factor + 1 se não adiável
};

- **Evento**
class Evento : public Appointment {
std::string nome, local;
int dur_dias = 0;
// factor() = 3, não adiável
};


- **Particular**
class Particular : public Appointment {
std::string motivo, local;
// factor() = base_factor + 1 se não adiável
};


#### 3. Lista Encadeada (linked_list.h/linked_list.cpp)

**Propósito:** Estrutura para armazenamento flexível  

**Estrutura:**
struct Node {
Appointment* data;
Node* next;
};

**Métodos:**  
- `list_push_back()` - Insere no final  
- `list_free()` - Libera memória (chama delete nos objetos)  
- `list_len()` - Conta elementos  
- `list_to_array()` - Converte para vetor  



#### 4. Sistema de Ordenação (sorting.h/sorting.cpp)

**Propósito:** Algoritmo genérico (Merge Sort)  

**Tipo de função de comparação:**
typedef int (CmpFn)(const void, const void*, void*);


**Método:**  
- `msort()` - Ordenação estável com função customizável  


#### 5. Parser de Arquivos (agenda_parser.h/agenda_parser.cpp)

**Propósito:** Leitura e interpretação dos arquivos de entrada  

**Métodos Principais:**  
- `parse_agenda()` - Processa arquivo agenda.txt  
- `parse_aula()`, `parse_orient()`, etc. - Parsers específicos  
- Funções utilitárias para parsing  



#### 6. Sistema de Conflitos (scheduler.h/scheduler.cpp)

**Propósito:** Resolução inteligente de conflitos  

**Estrutura Buckets:**
struct Buckets {
Appointment** confirmed = nullptr;
Appointment** delayed = nullptr;
Appointment** canceled = nullptr;
size_t nconf = 0, ndel = 0, ncanc = 0;
size_t cap_conf = 0, cap_del = 0, cap_canc = 0;
};

**Métodos:**  
- `buckets_init()` - Inicializa estrutura  
- `apply_filter()` - Algoritmo principal  
- `overlaps()` - Verifica sobreposição  
- `wins_over()` - Política de desempate  



#### 7. Funções de Comparação (comparators.h/comparators.cpp)

**Propósito:** Definição de critérios de ordenação  

**Comparadores:**  
- `cmp_by_datetime_asc()` - Cronológica crescente  
- `cmp_by_priority_desc()` - Prioridade decrescente  
- `cmp_by_duration_asc()` - Duração crescente  
- `cmp_by_id_asc()` - ID crescente  



#### 8. Gerador de Relatórios (file_writer.h/file_writer.cpp)

**Propósito:** Geração dos arquivos de saída formatados  

**Métodos:**  
- `write_confirmed()` - Confirmados (por data/hora)  
- `write_delayed()` - Adiados (por prioridade)  
- `write_canceled()` - Cancelados (por duração)  
- `write_all()` - Completo (por ID)  
- `pad_id()` - Formata ID com 6 dígitos  



#### 9. Sistema de Resultados (result_calculator.h/result_calculator.cpp)

**Propósito:** Processa `posicoes.txt` e calcula resultado final  

**Métodos:**  
- `read_positions()` - Lê posições do arquivo  
- `calculate_and_write_result()` - Calcula e escreve resultado  



## Funcionalidades Principais

- Leitura e parsing com tratamento de erros  
- Sistema OO com herança e polimorfismo  
- Resolução automática de conflitos com prioridade  
- Ordenação flexível e múltiplos critérios  
- Relatórios formatados sem linhas em branco finais  
- Tratamento de algarismos romanos para desempate  
- Modularidade, separação clara de responsabilidades  
- Gerenciamento automático de memória (destrutores virtuais)  



## Arquivos Gerados (pasta resultados/)

- `relatconfirmados.txt` - Confirmados (por data/hora)  
- `relatadiados.txt` - Adiados (por prioridade)  
- `relatcancelados.txt` - Cancelados (por duração)  
- `relatcompromissos.txt` - Completo (por ID)  
- `resultado.txt` - Resultado final (se existir `posicoes.txt`)  



## Melhorias em Relação à Versão C

- Sistema OO nativo: classes, herança, polimorfismo  
- Gerenciamento automático com destrutores virtuais e RAII  
- Strings da STL para maior segurança  
- Tipagem forte com enum class  
- Organização modular clara  
- Sintaxe mais limpa