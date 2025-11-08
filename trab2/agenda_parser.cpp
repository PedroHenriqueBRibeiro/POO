#include "agenda_parser.h"
#include "utils.h"
#include "datetime.h"
#include "appointments.h"
#include <unistd.h>
#include <errno.h>

Appointment* parse_aula(std::FILE* f, int id) {
    char line[256], data[64], hora[64], disc[64], nivel[64]; int dur, grau;
    read_line_req(f, line, sizeof(line)); std::sscanf(line, "%63s %63s", data, hora);
    read_line_req(f, line, sizeof(line)); dur = std::atoi(line);
    read_line_req(f, disc, sizeof(disc)); read_line_req(f, nivel, sizeof(nivel));
    read_line_req(f, line, sizeof(line)); grau = std::atoi(line);
    Aula* p = new Aula(); p->id = id; p->grau_prior = grau; p->adiavel = false;
    p->disciplina = disc; p->nivel = nivel;
    p->ini = parse_date(data); parse_time_into(&p->ini, hora); p->fim = p->ini; add_minutes(&p->fim, dur); p->dur_min = dur;
    p->describe(); ensure_blank_line(f); return p;
}

Appointment* parse_orient(std::FILE* f, int id) {
    char line[256], data[64], hora[64], aluno[64], nivel[64], adiavel[16], assunto[64]; int dur, grau;
    read_line_req(f, line, sizeof(line)); std::sscanf(line, "%63s %63s", data, hora);
    read_line_req(f, line, sizeof(line)); dur = std::atoi(line);
    read_line_req(f, adiavel, sizeof(adiavel));
    read_line_req(f, aluno, sizeof(aluno)); read_line_req(f, nivel, sizeof(nivel));
    read_line_req(f, assunto, sizeof(assunto));
    read_line_req(f, line, sizeof(line)); grau = std::atoi(line);
    Orient* p = new Orient(); p->id = id; p->grau_prior = grau; p->adiavel = parse_bool(adiavel);
    p->aluno = aluno; p->nivel = nivel; p->assunto = assunto;
    p->ini = parse_date(data); parse_time_into(&p->ini, hora); p->fim = p->ini; add_minutes(&p->fim, dur); p->dur_min = dur;
    p->describe(); ensure_blank_line(f); return p;
}

Appointment* parse_reuniao(std::FILE* f, int id) {
    char line[256], data[64], hora[64], adiavel[16], assunto[64]; int dur, grau;
    read_line_req(f, line, sizeof(line)); std::sscanf(line, "%63s %63s", data, hora);
    read_line_req(f, line, sizeof(line)); dur = std::atoi(line);
    read_line_req(f, adiavel, sizeof(adiavel)); read_line_req(f, assunto, sizeof(assunto));
    read_line_req(f, line, sizeof(line)); grau = std::atoi(line);
    Reuniao* p = new Reuniao(); p->id = id; p->grau_prior = grau; p->adiavel = parse_bool(adiavel);
    p->assunto = assunto;
    p->ini = parse_date(data); parse_time_into(&p->ini, hora); p->fim = p->ini; add_minutes(&p->fim, dur); p->dur_min = dur;
    p->describe(); ensure_blank_line(f); return p;
}

Appointment* parse_evento(std::FILE* f, int id) {
    char line[256], data[64], hora[64], nome[64], local[64]; int dur_dias, grau;
    read_line_req(f, line, sizeof(line)); std::sscanf(line, "%63s %63s", data, hora);
    read_line_req(f, line, sizeof(line)); dur_dias = std::atoi(line);
    read_line_req(f, nome, sizeof(nome)); read_line_req(f, local, sizeof(local));
    read_line_req(f, line, sizeof(line)); grau = std::atoi(line);
    Evento* p = new Evento(); p->id = id; p->grau_prior = grau; p->adiavel = false; p->dur_dias = dur_dias;
    p->nome = nome; p->local = local;
    p->ini = parse_date(data); parse_time_into(&p->ini, hora); p->fim = p->ini; add_days(&p->fim, dur_dias); p->dur_min = dur_dias * 24 * 60;
    p->describe(); ensure_blank_line(f); return p;
}

Appointment* parse_particular(std::FILE* f, int id) {
    char line[256], data[64], hora[64], motivo[64], local[64], adiavel[16]; int dur, grau;
    read_line_req(f, line, sizeof(line)); std::sscanf(line, "%63s %63s", data, hora);
    read_line_req(f, line, sizeof(line)); dur = std::atoi(line);
    read_line_req(f, adiavel, sizeof(adiavel)); read_line_req(f, motivo, sizeof(motivo));
    read_line_req(f, local, sizeof(local)); read_line_req(f, line, sizeof(line)); grau = std::atoi(line);
    Particular* p = new Particular(); p->id = id; p->grau_prior = grau; p->adiavel = parse_bool(adiavel);
    p->motivo = motivo; p->local = local;
    p->ini = parse_date(data); parse_time_into(&p->ini, hora); p->fim = p->ini; add_minutes(&p->fim, dur); p->dur_min = dur;
    p->describe(); ensure_blank_line(f); return p;
}

Node* parse_agenda(const char* path) {
    char cwd[1024] = ""; 
    if (getcwd(cwd, sizeof(cwd)) != nullptr) {
        std::fprintf(stderr, "[debug] CWD: %s\n", cwd);
    } else {
        std::fprintf(stderr, "[debug] Não foi possível obter CWD\n");
    }

    std::FILE* f = std::fopen(path, "r");
    if (!f) {
        std::fprintf(stderr, "[erro] Não foi possível abrir '%s'\n", path);
        std::perror("[errno]");
        f = std::fopen("agenda", "r");
        if (!f) {
            std::fprintf(stderr, "[erro] Falhou também 'agenda' sem extensão.\n");
            std::exit(1);
        }
        else {
            std::fprintf(stderr, "[debug] Abrindo 'agenda' (sem .txt)\n");
        }
    }
    else {
        std::fprintf(stderr, "[debug] Abriu '%s'\n", path);
    }

    Node* head = nullptr; char line[256]; size_t headers = 0;
    while (std::fgets(line, sizeof(line), f)) {
        trim_newline(line);
        if (line[0] == '\0') continue;
        if (!is_header_line(line)) continue;
        headers++;
        char tchar = line[0]; int id = parse_id(line); Appointment* a = nullptr;
        if (tchar == 'A') a = parse_aula(f, id);
        else if (tchar == 'O') a = parse_orient(f, id);
        else if (tchar == 'R') a = parse_reuniao(f, id);
        else if (tchar == 'E') a = parse_evento(f, id);
        else if (tchar == 'P') a = parse_particular(f, id);
        head = list_push_back(head, a);
    }
    std::fclose(f);
    std::fprintf(stderr, "[debug] parse_agenda: headers válidos lidos = %zu\n", headers);
    return head;
}