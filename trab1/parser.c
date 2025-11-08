#include "parser.h"
#include "util.h"
#include "datetime.h"
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <unistd.h>


static int aula_factor(const Appointment *a) { (void)a; return 2; }
static int aula_is_adiavel(const Appointment *a) { (void)a; return 0; }
static void aula_describe(const Appointment *a, char *out, size_t cap) {
    const Aula *p = (const Aula *)a;
    snprintf(out, cap, "Aula de %s", p->disciplina);
}
static void aula_data_full(const Appointment *a, char *out, size_t cap) {
    const Aula *p = (const Aula *)a;
    snprintf(out, cap, "%s", p->disciplina);
}

static int orient_factor(const Appointment *a) {
    const Orient *p = (const Orient *)a;
    int f = base_factor(p->base.tipo);
    if (!p->base.adiavel) f += 1;
    return f;
}
static int orient_is_adiavel(const Appointment *a) {
    return ((const Orient *)a)->base.adiavel;
}
static void orient_describe(const Appointment *a, char *out, size_t cap) {
    const Orient *p = (const Orient *)a;
    snprintf(out, cap, "Orientação de %s", p->aluno);
}
static void orient_data_full(const Appointment *a, char *out, size_t cap) {
    const Orient *p = (const Orient *)a;
    snprintf(out, cap, "%s", p->aluno);
}

static int reun_factor(const Appointment *a) {
    const Reuniao *p = (const Reuniao *)a;
    int f = base_factor(p->base.tipo);
    if (!p->base.adiavel) f += 1;
    return f;
}
static int reun_is_adiavel(const Appointment *a) {
    return ((const Reuniao *)a)->base.adiavel;
}
static void reun_describe(const Appointment *a, char *out, size_t cap) {
    (void)a;
    snprintf(out, cap, "Reunião de Departamento");
}
static void reun_data_full(const Appointment *a, char *out, size_t cap) {
    (void)a;
    snprintf(out, cap, "Reunião de Departamento");
}

static int evento_factor(const Appointment *a) { (void)a; return 3; }
static int evento_is_adiavel(const Appointment *a) { (void)a; return 0; }
static void evento_describe(const Appointment *a, char *out, size_t cap) {
    const Evento *p = (const Evento *)a;
    snprintf(out, cap, "%s", p->nome);
}
static void evento_data_full(const Appointment *a, char *out, size_t cap) {
    const Evento *p = (const Evento *)a;
    snprintf(out, cap, "%s", p->nome);
}

static int part_factor(const Appointment *a) {
    const Particular *p = (const Particular *)a;
    int f = base_factor(p->base.tipo);
    if (!p->base.adiavel) f += 1;
    return f;
}
static int part_is_adiavel(const Appointment *a) {
    return ((const Particular *)a)->base.adiavel;
}
static void part_describe(const Appointment *a, char *out, size_t cap) {
    const Particular *p = (const Particular *)a;
    snprintf(out, cap, "%s", p->motivo);
}
static void part_data_full(const Appointment *a, char *out, size_t cap) {
    const Particular *p = (const Particular *)a;
    snprintf(out, cap, "%s", p->motivo);
}

// Definições das VTables
const AppointmentVTable VT_AULA = {aula_factor, aula_is_adiavel, aula_describe, aula_data_full};
const AppointmentVTable VT_ORIENT = {orient_factor, orient_is_adiavel, orient_describe, orient_data_full};
const AppointmentVTable VT_REUNIAO = {reun_factor, reun_is_adiavel, reun_describe, reun_data_full};
const AppointmentVTable VT_EVENTO = {evento_factor, evento_is_adiavel, evento_describe, evento_data_full};
const AppointmentVTable VT_PART = {part_factor, part_is_adiavel, part_describe, part_data_full};

// Resto das funções do parser (permanecem iguais)

int parse_id(const char *s) {
    if (!isalpha((unsigned char)s[0])) {
        fprintf(stderr, "Tipo inválido: %s\n", s);
        exit(1);
    }
    return atoi(s + 1);
}

void zero_base(Appointment *b, Tipo t, int id) {
    memset(b, 0, sizeof(*b));
    b->tipo = t;
    b->id = id;
    b->forced_by = -1;
}

Appointment *parse_aula(FILE *f, int id) {
    char line[256], data[64], hora[64], disc[MAX_STR], nivel[MAX_STR];
    int dur, grau;
    read_line_req(f, line, sizeof(line));
    sscanf(line, "%63s %63s", data, hora);
    read_line_req(f, line, sizeof(line));
    dur = atoi(line);
    read_line_req(f, disc, sizeof(disc));
    read_line_req(f, nivel, sizeof(nivel));
    read_line_req(f, line, sizeof(line));
    grau = atoi(line);
    
    Aula *p = (Aula *)malloc(sizeof(Aula));
    zero_base(&p->base, T_AULA, id);
    p->base.vptr = &VT_AULA;
    p->base.grau_prior = grau;
    p->base.adiavel = 0;
    strncpy(p->disciplina, disc, MAX_STR - 1);
    p->disciplina[MAX_STR - 1] = 0;
    strncpy(p->nivel, nivel, MAX_STR - 1);
    p->nivel[MAX_STR - 1] = 0;
    p->base.ini = parse_date(data);
    parse_time_into(&p->base.ini, hora);
    p->base.fim = p->base.ini;
    add_minutes(&p->base.fim, dur);
    p->base.dur_min = dur;
    appt_fill_descricao(&p->base);
    ensure_blank_line(f);
    return (Appointment *)p;
}

Appointment *parse_orient(FILE *f, int id) {
    char line[256], data[64], hora[64], aluno[MAX_STR], nivel[MAX_STR], adiavel[16], assunto[MAX_STR];
    int dur, grau;
    read_line_req(f, line, sizeof(line));
    sscanf(line, "%63s %63s", data, hora);
    read_line_req(f, line, sizeof(line));
    dur = atoi(line);
    read_line_req(f, adiavel, sizeof(adiavel));
    read_line_req(f, aluno, sizeof(aluno));
    read_line_req(f, nivel, sizeof(nivel));
    read_line_req(f, assunto, sizeof(assunto));
    read_line_req(f, line, sizeof(line));
    grau = atoi(line);
    
    Orient *p = (Orient *)malloc(sizeof(Orient));
    zero_base(&p->base, T_ORIENT, id);
    p->base.vptr = &VT_ORIENT;
    p->base.grau_prior = grau;
    p->base.adiavel = parse_bool(adiavel);
    strncpy(p->aluno, aluno, MAX_STR - 1);
    p->aluno[MAX_STR - 1] = 0;
    strncpy(p->nivel, nivel, MAX_STR - 1);
    p->nivel[MAX_STR - 1] = 0;
    strncpy(p->assunto, assunto, MAX_STR - 1);
    p->assunto[MAX_STR - 1] = 0;
    p->base.ini = parse_date(data);
    parse_time_into(&p->base.ini, hora);
    p->base.fim = p->base.ini;
    add_minutes(&p->base.fim, dur);
    p->base.dur_min = dur;
    appt_fill_descricao(&p->base);
    ensure_blank_line(f);
    return (Appointment *)p;
}

Appointment *parse_reuniao(FILE *f, int id) {
    char line[256], data[64], hora[64], adiavel[16], assunto[MAX_STR];
    int dur, grau;
    read_line_req(f, line, sizeof(line));
    sscanf(line, "%63s %63s", data, hora);
    read_line_req(f, line, sizeof(line));
    dur = atoi(line);
    read_line_req(f, adiavel, sizeof(adiavel));
    read_line_req(f, assunto, sizeof(assunto));
    read_line_req(f, line, sizeof(line));
    grau = atoi(line);
    
    Reuniao *p = (Reuniao *)malloc(sizeof(Reuniao));
    zero_base(&p->base, T_REUNIAO, id);
    p->base.vptr = &VT_REUNIAO;
    p->base.grau_prior = grau;
    p->base.adiavel = parse_bool(adiavel);
    p->base.ini = parse_date(data);
    parse_time_into(&p->base.ini, hora);
    p->base.fim = p->base.ini;
    add_minutes(&p->base.fim, dur);
    p->base.dur_min = dur;
    appt_fill_descricao(&p->base);
    strncpy(p->assunto, assunto, MAX_STR - 1);
    p->assunto[MAX_STR - 1] = 0;
    ensure_blank_line(f);
    return (Appointment *)p;
}

Appointment *parse_evento(FILE *f, int id) {
    char line[256], data[64], hora[64], nome[MAX_STR], local[MAX_STR];
    int dur_dias, grau;
    read_line_req(f, line, sizeof(line));
    sscanf(line, "%63s %63s", data, hora);
    read_line_req(f, line, sizeof(line));
    dur_dias = atoi(line);
    read_line_req(f, nome, sizeof(nome));
    read_line_req(f, local, sizeof(local));
    read_line_req(f, line, sizeof(line));
    grau = atoi(line);
    
    Evento *p = (Evento *)malloc(sizeof(Evento));
    zero_base(&p->base, T_EVENTO, id);
    p->base.vptr = &VT_EVENTO;
    p->base.grau_prior = grau;
    p->base.adiavel = 0;
    strncpy(p->nome, nome, MAX_STR - 1);
    p->nome[MAX_STR - 1] = 0;
    strncpy(p->local, local, MAX_STR - 1);
    p->local[MAX_STR - 1] = 0;
    p->dur_dias = dur_dias;
    p->base.ini = parse_date(data);
    parse_time_into(&p->base.ini, hora);
    p->base.fim = p->base.ini;
    add_days(&p->base.fim, dur_dias);
    p->base.dur_min = dur_dias * 24 * 60;
    appt_fill_descricao(&p->base);
    ensure_blank_line(f);
    return (Appointment *)p;
}

Appointment *parse_particular(FILE *f, int id) {
    char line[256], data[64], hora[64], motivo[MAX_STR], local[MAX_STR], adiavel[16];
    int dur, grau;
    read_line_req(f, line, sizeof(line));
    sscanf(line, "%63s %63s", data, hora);
    read_line_req(f, line, sizeof(line));
    dur = atoi(line);
    read_line_req(f, adiavel, sizeof(adiavel));
    read_line_req(f, motivo, sizeof(motivo));
    read_line_req(f, local, sizeof(local));
    read_line_req(f, line, sizeof(line));
    grau = atoi(line);
    
    Particular *p = (Particular *)malloc(sizeof(Particular));
    zero_base(&p->base, T_PARTICULAR, id);
    p->base.vptr = &VT_PART;
    p->base.grau_prior = grau;
    p->base.adiavel = parse_bool(adiavel);
    strncpy(p->motivo, motivo, MAX_STR - 1);
    p->motivo[MAX_STR - 1] = 0;
    strncpy(p->local, local, MAX_STR - 1);
    p->local[MAX_STR - 1] = 0;
    p->base.ini = parse_date(data);
    parse_time_into(&p->base.ini, hora);
    p->base.fim = p->base.ini;
    add_minutes(&p->base.fim, dur);
    p->base.dur_min = dur;
    appt_fill_descricao(&p->base);
    ensure_blank_line(f);
    return (Appointment *)p;
}

Node *parse_agenda(const char *path) {
    char cwd[1024] = "";
    getcwd(cwd, sizeof(cwd));
    fprintf(stderr, "[debug] CWD: %s\n", cwd);
    
    FILE *f = fopen(path, "r");
    if (!f) {
        fprintf(stderr, "[erro] Não foi possível abrir '%s'\n", path);
        perror("[errno]");
        f = fopen("agenda", "r");
        if (!f) {
            fprintf(stderr, "[erro] Falhou também 'agenda' sem extensão.\n");
            exit(1);
        } else {
            fprintf(stderr, "[debug] Abrindo 'agenda' (sem .txt)\n");
        }
    } else {
        fprintf(stderr, "[debug] Abriu '%s'\n", path);
    }
    
    Node *head = NULL;
    char line[256];
    size_t headers = 0;
    
    while (fgets(line, sizeof(line), f)) {
        trim_newline(line);
        if (line[0] == '\0') continue;
        if (!is_header_line(line)) continue;
        headers++;
        char tchar = line[0];
        int id = parse_id(line);
        Appointment *a = NULL;
        
        if (tchar == 'A') a = parse_aula(f, id);
        else if (tchar == 'O') a = parse_orient(f, id);
        else if (tchar == 'R') a = parse_reuniao(f, id);
        else if (tchar == 'E') a = parse_evento(f, id);
        else if (tchar == 'P') a = parse_particular(f, id);
        
        head = list_push_back(head, a);
    }
    
    fclose(f);
    fprintf(stderr, "[debug] parse_agenda: headers válidos lidos = %zu\n", headers);
    return head;
}