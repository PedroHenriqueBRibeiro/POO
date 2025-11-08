#include "appointments.h"

int base_factor(Tipo t) {
    switch (t) {
    case Tipo::AULA: return 2;
    case Tipo::ORIENT: return 1;
    case Tipo::REUNIAO: return 4;
    case Tipo::EVENTO: return 3;
    case Tipo::PARTICULAR: return 2;
    default: return 1;
    }
}

int tipo_rank_for_tiebreak(Tipo t) {
    switch (t) {
    case Tipo::REUNIAO: return 5;
    case Tipo::EVENTO: return 4;
    case Tipo::AULA: return 3;
    case Tipo::PARTICULAR: return 2;
    case Tipo::ORIENT: return 1;
    default: return 0;
    }
}