#include "agenda_parser.h"
#include "scheduler.h"
#include "file_writer.h"
#include "result_calculator.h"
#include "linked_list.h"
#include <cstdlib>
#include <sys/stat.h>
#include <cstdio>


static void create_dir_if_not_exists(const char* dirname) {
    struct stat st;
    if (stat(dirname, &st) == -1) {
        mkdir(dirname, 0755);
    }
}

int main(){
    const char* path_agenda = "agenda.txt";
    const char* path_posicoes = "posicoes.txt";
    const char* path_resultados = "resultados";
    create_dir_if_not_exists(path_resultados);

    std::fprintf(stderr, "[debug] lendo arquivos da pasta atual\n");
    std::fprintf(stderr, "[debug] caminho agenda: %s\n", path_agenda);
    std::fprintf(stderr, "[debug] caminho posicoes: %s\n", path_posicoes);
    std::fprintf(stderr, "[debug] pasta resultados: %s\n", path_resultados);

    Node* agenda_list = parse_agenda(path_agenda);
    if (!agenda_list) {
        std::fprintf(stderr, "Erro ao ler %s\n", path_agenda);
        return 1;
    }
    std::fprintf(stderr, "[debug] parse_agenda OK\n");

    size_t N = 0;
    Appointment** A = list_to_array(agenda_list, &N);
    std::fprintf(stderr, "[debug] total lidos (N) = %zu\n", N);

    Buckets B;
    apply_filter(A, (int)N, &B);
    std::fprintf(stderr, "[debug] buckets => confirmados=%zu, adiados=%zu, cancelados=%zu\n",
            B.nconf, B.ndel, B.ncanc);
    std::fprintf(stderr, "[debug] adiados (N=%zu):", B.ndel);
    for (size_t t = 0; t < B.ndel; t++) std::fprintf(stderr, " %06d", B.delayed[t]->id);
    std::fprintf(stderr, "\n");
    char relat_confirmados[256], relat_adiados[256], relat_cancelados[256], relat_compromissos[256], relat_resultado[256];
    
    std::snprintf(relat_confirmados, sizeof(relat_confirmados), "%s/relatconfirmados.txt", path_resultados);
    std::snprintf(relat_adiados, sizeof(relat_adiados), "%s/relatadiados.txt", path_resultados);
    std::snprintf(relat_cancelados, sizeof(relat_cancelados), "%s/relatcancelados.txt", path_resultados);
    std::snprintf(relat_compromissos, sizeof(relat_compromissos), "%s/relatcompromissos.txt", path_resultados);
    std::snprintf(relat_resultado, sizeof(relat_resultado), "%s/resultado.txt", path_resultados);

    write_confirmed(relat_confirmados, B.confirmed, (int)B.nconf);
    std::fprintf(stderr, "[debug] wrote %s\n", relat_confirmados);

    write_delayed(relat_adiados, B.delayed, (int)B.ndel);
    std::fprintf(stderr, "[debug] wrote %s\n", relat_adiados);

    write_canceled(relat_cancelados, B.canceled, (int)B.ncanc);
    std::fprintf(stderr, "[debug] wrote %s\n", relat_cancelados);

    Appointment** A_all = (Appointment**)std::malloc(sizeof(Appointment*) * N);
    for (size_t i = 0; i < N; i++) {
        A_all[i] = A[i];
    }
    write_all(relat_compromissos, A_all, (int)N);
    std::fprintf(stderr, "[debug] wrote %s\n", relat_compromissos);

    int i = 0, j = 0, k = 0, m = 0;
    if (!read_positions(path_posicoes, &i, &j, &k, &m)) {
        std::fprintf(stderr, "[debug] posicoes.txt NÃO encontrado. Pulando resultado.txt\n");
    } else {
        std::fprintf(stderr, "[debug] posicoes: %d %d %d %d\n", i, j, k, m);
        calculate_and_write_result(B, A, N, i, j, k, m);
        std::fprintf(stderr, "[debug] wrote %s\n", relat_resultado);
    }

    std::free(A_all);
    std::free(A);
    list_free(agenda_list);
    
    if (B.confirmed) std::free(B.confirmed);
    if (B.delayed) std::free(B.delayed);
    if (B.canceled) std::free(B.canceled);
    
    return 0;
}