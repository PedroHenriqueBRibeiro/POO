#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include "util.h"
#include "appointment.h"
#include "list.h"
#include "parser.h"
#include "buckets.h"
#include "writers.h"
#include "resultado.h"
#include "sort.h"
#include "comparators.h"

static void create_dir_if_not_exists(const char* dirname) {
    struct stat st = {0};
    if (stat(dirname, &st) == -1) {
        mkdir(dirname, 0755);
    }
}

int main(void) {
    const char* path_agenda = "agenda.txt";
    const char* path_posicoes = "posicoes.txt";
    const char* path_resultados = "resultados";
    create_dir_if_not_exists(path_resultados);

    fprintf(stderr, "[debug] lendo arquivos da pasta atual\n");
    fprintf(stderr, "[debug] caminho agenda: %s\n", path_agenda);
    fprintf(stderr, "[debug] caminho posicoes: %s\n", path_posicoes);
    fprintf(stderr, "[debug] pasta resultados: %s\n", path_resultados);

    Node *agenda_list = parse_agenda(path_agenda);
    if (!agenda_list) {
        fprintf(stderr, "Erro ao ler %s\n", path_agenda);
        return 1;
    }
    fprintf(stderr, "[debug] parse_agenda OK\n");

    size_t N = 0;
    Appointment **A = (Appointment **)list_to_array(agenda_list, &N);
    fprintf(stderr, "[debug] total lidos (N) = %zu\n", N);

    Buckets B;
    buckets_init(&B);
    apply_filter(A, (int)N, &B);
    fprintf(stderr, "[debug] buckets => confirmados=%zu, adiados=%zu, cancelados=%zu\n",
            B.nconf, B.ndel, B.ncanc);

    fprintf(stderr, "[debug] adiados (N=%zu):", B.ndel);
    for (size_t t = 0; t < B.ndel; t++) fprintf(stderr, " %06d", B.delayed[t]->id);
    fprintf(stderr, "\n");
    char relat_confirmados[256], relat_adiados[256], relat_cancelados[256], relat_compromissos[256], relat_resultado[256];
    
    snprintf(relat_confirmados, sizeof(relat_confirmados), "%s/relatconfirmados.txt", path_resultados);
    snprintf(relat_adiados, sizeof(relat_adiados), "%s/relatadiados.txt", path_resultados);
    snprintf(relat_cancelados, sizeof(relat_cancelados), "%s/relatcancelados.txt", path_resultados);
    snprintf(relat_compromissos, sizeof(relat_compromissos), "%s/relatcompromissos.txt", path_resultados);
    snprintf(relat_resultado, sizeof(relat_resultado), "%s/resultado.txt", path_resultados);

    write_confirmed(relat_confirmados, B.confirmed, (int)B.nconf);
    fprintf(stderr, "[debug] wrote %s\n", relat_confirmados);

    write_delayed(relat_adiados, B.delayed, (int)B.ndel);
    fprintf(stderr, "[debug] wrote %s\n", relat_adiados);

    write_canceled(relat_cancelados, B.canceled, (int)B.ncanc);
    fprintf(stderr, "[debug] wrote %s\n", relat_cancelados);

    Appointment **A_all = (Appointment **)malloc(sizeof(Appointment *) * N);
    for (size_t i = 0; i < N; i++) A_all[i] = A[i];
    write_all(relat_compromissos, A_all, (int)N);
    fprintf(stderr, "[debug] wrote %s\n", relat_compromissos);

    int i = 0, j = 0, k = 0, m = 0;
    if (!read_positions(path_posicoes, &i, &j, &k, &m)) {
        fprintf(stderr, "[debug] posicoes.txt NÃO encontrado. Pulando resultado.txt\n");
    } else {
        fprintf(stderr, "[debug] posicoes: %d %d %d %d\n", i, j, k, m);

        Appointment **CONF = (Appointment **)malloc(sizeof(Appointment *) * B.nconf);
        for (size_t t = 0; t < B.nconf; ++t) CONF[t] = B.confirmed[t];
        msort((void **)CONF, (int)B.nconf, cmp_by_datetime_asc, NULL);

        Appointment **DEL = (Appointment **)malloc(sizeof(Appointment *) * B.ndel);
        for (size_t t = 0; t < B.ndel; ++t) DEL[t] = B.delayed[t];
        msort((void **)DEL, (int)B.ndel, cmp_by_priority_desc, NULL);

        Appointment **CANC = (Appointment **)malloc(sizeof(Appointment *) * B.ncanc);
        for (size_t t = 0; t < B.ncanc; ++t) CANC[t] = B.canceled[t];
        msort((void **)CANC, (int)B.ncanc, cmp_by_duration_asc, NULL);

        Appointment **ALL = (Appointment **)malloc(sizeof(Appointment *) * N);
        for (size_t t = 0; t < N; ++t) ALL[t] = A[t];
        msort((void **)ALL, (int)N, cmp_by_id_asc, NULL);

        show_pick((const Appointment *const *)CONF, B.nconf, i, "CONF");
        show_pick((const Appointment *const *)DEL, B.ndel, j, "DEL ");
        show_pick((const Appointment *const *)CANC, B.ncanc, k, "CANC");
        show_pick((const Appointment *const *)ALL, N, m, "ALL ");

        write_result_sum(relat_resultado,
                         CONF, (int)B.nconf,
                         DEL, (int)B.ndel,
                         CANC, (int)B.ncanc,
                         ALL, (int)N,
                         i, j, k, m);
        fprintf(stderr, "[debug] wrote %s\n", relat_resultado);

        free(CONF);
        free(DEL);
        free(CANC);
        free(ALL);
    }

    free(A_all);
    free(A);
    list_free(agenda_list, free_appt);
    return 0;
}