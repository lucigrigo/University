/*
            Grigore Lucian-Florin
            Algoritmi Paraleli si Distribuiti
            Tema 3
*/

// librariile utilizate
#include <iostream>
#include "mpi.h"
#include <fstream>
#include <string.h>
#include <vector>
#include <queue>
#include <unistd.h>

// macro-uri folosite pentru rezolvare
#define NO_WORKERS 5
#define MASTER 0
#define NO_READER_THREADS 4
#define MASTER_COMM_ID 0
#define RECEIVER_ID 0

using namespace std;

// variabile si constante folosite in rezolvare
const string _CONSONANTS = "qwrtpsdfghjklzxcvbnm";
const string _BIG_CONSONANTS = "QWRTPSDFGHJKLZXCVBNM";

const string genres[] =
    {
        "horror",
        "comedy",
        "fantasy",
        "science-fiction"};

typedef struct
{
    char *input_filename;
    int thread_id;
} TReaderArgs;

typedef struct
{
    int *index;
    bool done;
    string genre;
    char *paragraph;
} TParagraph;

// unde vor fi stocate paragrafele pentru fiecare gen
vector<TParagraph> horror_paragraphs;
vector<TParagraph> comedy_paragraphs;
vector<TParagraph> fantasy_paragraphs;
vector<TParagraph> sf_paragraphs;

vector<TParagraph> *paragraphs[] = {
    &horror_paragraphs,
    &comedy_paragraphs,
    &fantasy_paragraphs,
    &sf_paragraphs};

int no_threads;
static pthread_mutex_t first_editor_mutex;
static pthread_mutex_t second_editor_mutex;
static queue<TParagraph> unedited_pars;
static queue<TParagraph> edited_pars;

// functie care editeaza un char* pentru genul horror
char *edit_horror(char *src, int size)
{
    string dst;

    for (int i = 0; src[i] != '\0'; ++i)
    {
        char c = src[i];

        if (_CONSONANTS.find(c) != string::npos)
        {
            dst += c;
            dst += c;
        }
        else if (_BIG_CONSONANTS.find(c) != string::npos)
        {
            dst += c;
            dst += (c + 32);
        }
        else
            dst += c;
    }
    dst += '\0';

    char *edited = (char *)malloc(dst.size() * sizeof(char));
    dst.copy(edited, dst.size(), 0);
    return edited;
}

// functie care editeaza un char* pentru genul comedy
char *edit_comedy(char *src, int size)
{
    string dst;

    for (int i = 0, index = 1; src[i] != '\0'; ++i)
    {
        char c = src[i];

        if (c == ' ' || c == '\n' || c == '\0')
            index = 0;

        if (index % 2 == 0)
        {
            if (c >= 'a' && c <= 'z')
            {
                c -= 32;
            }
        }

        dst += c;
        ++index;
    }
    dst += '\0';

    char *edited = (char *)malloc(dst.size() * sizeof(char));
    dst.copy(edited, dst.size(), 0);

    return edited;
}

// functie care editeaza un char* pentru genul fantasy
char *edit_fantasy(char *src, int size)
{
    string dst;

    bool prev_space = true;
    for (int i = 0; src[i] != '\0'; ++i)
    {
        char c = src[i];
        
        if (prev_space && c != ' ' && c != '\n' && c != '\0')
        {
            if (c >= 'a' && c <= 'z')
                c -= 32;

            prev_space = false;
        }
        else if (c == ' ' || c == '\n')
            prev_space = true;

        dst += c;
    }
    dst += '\0';

    char *edited = (char *)malloc(dst.size() * sizeof(char));
    dst.copy(edited, dst.size(), 0);

    return edited;
}

// functie care editeaza un char* pentru genul science-fiction
char *edit_sf(char *src, int size)
{
    string dst;

    for (int i = 0, count = 1; src[i] != '\0'; ++i)
    {
        char c = src[i];

        if (count == 7)
        {
            int len = 0, index = i;

            while (src[index] != ' ' && src[index] != '\n' && src[index] != '\0')
            {
                ++len;
                ++index;
            }
            --index;
            i = index;

            char *w = (char *)malloc(len * sizeof(char));
            int j = 0;
            while (len > 0)
            {
                w[j++] = src[index];
                dst += src[index];
                --len;
                --index;
            }

            count = 0;
        }
        else
            dst += c;
        if (c == ' ')
            ++count;
        if (c == '\n')
            count = 1;
    }
    dst += '\0';

    char *edited = (char *)malloc(dst.size() * sizeof(char));
    dst.copy(edited, dst.size(), 0);

    return edited;
}

// tip de date pentru a memora pointeri catre functiile de editare
typedef char *(*edit_function)(char *src, int size);

// vector cu funtiile de editare
const edit_function edit_functions[] = {
    edit_horror,
    edit_comedy,
    edit_fantasy,
    edit_sf};

// functie care se ocupa de un thread lansat de MASTER
// care citeste din input pentru un singur gen, in functie de rank
void *_reader_thread(void *arg)
{
    TReaderArgs *args = (TReaderArgs *)arg;
    int thread_id = args->thread_id, status;
    string genre = genres[thread_id];
    string input_filename = args->input_filename;
    vector<TParagraph> *pars = paragraphs[thread_id];
    ifstream input_file(input_filename);
    string line;
    int par_index = 0;

    // citesc din fisierul de input pana gasesc genul asociat thread-ului curent
    while (getline(input_file, line))
    {
        if (line == "" || line == "\n")
            ++par_index;

        if (line == genre)
        {
            // daca gasesc genul asociat
            string paragraph;
            string s;
            int index = 0;
            int step = 0;

            // incep sa citesc din paragraf
            while (getline(input_file, s))
            {
                if (s == "")
                    break;

                // odata la 20 de linii, trimit catre workerul genului
                if (step == 20)
                {
                    int size = paragraph.size();
                    MPI_Send(&size, 1, MPI_INT, thread_id + 1, 0, MPI_COMM_WORLD);
                    MPI_Send(&par_index, 1, MPI_INT, thread_id + 1, 0, MPI_COMM_WORLD);
                    MPI_Send(paragraph.c_str(), paragraph.size(), MPI_CHAR, thread_id + 1, 0, MPI_COMM_WORLD);
                    paragraph.clear();
                    step = 0;
                }

                paragraph.append(s);
                paragraph.append(" \n");
            }

            // aici se ajunge cand ultima bucata din paragraf are mai putin de 20 de linii
            if (!paragraph.empty())
            {
                int size = paragraph.size();
                MPI_Send(&size, 1, MPI_INT, thread_id + 1, 0, MPI_COMM_WORLD);
                MPI_Send(&par_index, 1, MPI_INT, thread_id + 1, 0, MPI_COMM_WORLD);
                MPI_Send(paragraph.c_str(), paragraph.size(), MPI_CHAR, thread_id + 1, 0, MPI_COMM_WORLD);
            }

            // semnal ca am terminat paragraful
            int done_par = 0;
            MPI_Send(&done_par, 1, MPI_INT, thread_id + 1, 0, MPI_COMM_WORLD);
            ++par_index;
        }
    }

    input_file.close();

    // semnal ca am terminat fisierul
    int done = -1;
    MPI_Send(&done, 1, MPI_INT, thread_id + 1, 0, MPI_COMM_WORLD);

    // incep sa primesc de la worker paragrafele dupa editare
    int size;
    MPI_Recv(&size, 1, MPI_INT, thread_id + 1, 0, MPI_COMM_WORLD, NULL);

    while(size != 0) {
        TParagraph p;
        p.done = true;
        p.genre = genre;
        p.index = (int *)malloc(sizeof(int));

        MPI_Recv(&par_index, 1, MPI_INT, thread_id + 1, 0, MPI_COMM_WORLD, NULL);
        (*p.index) = par_index;

        char *recv = (char *)malloc((size + 1) * sizeof(char));
        MPI_Recv(recv, size, MPI_CHAR, thread_id + 1, 0, MPI_COMM_WORLD, NULL);
        recv[size] = '\0';
        p.paragraph = recv;

        // paragrafele sunt puse in vectorul asociat genului curent
        pars->push_back(p);

        MPI_Recv(&size, 1, MPI_INT, thread_id + 1, 0, MPI_COMM_WORLD, NULL);
    }

    pthread_exit(NULL);
}

// functie care executa un thread pentru un worker de editare
void *_editor_thread(void *arg)
{
    int rank = *(int *)arg, status, worker_rank;
    MPI_Comm_rank(MPI_COMM_WORLD, &worker_rank);
    string genre = genres[worker_rank - 1];

    // vad daca sunt receiver (comunicare cu master) - adica rank 0
    if (rank == RECEIVER_ID)
    {
        // pornesc thread-urile de editare
        pthread_t editing_threads[no_threads - 1];
        int editing_args[no_threads - 1];

        for (int i = 0; i < no_threads - 1; ++i)
        {
            editing_args[i] = i + 1;
            int status = pthread_create(&editing_threads[i], NULL, _editor_thread, &editing_args[i]);
        }

        int no_pars = 0;
        // intru in bucla infinita si astept paragrafe incontinuu de la master
        while (true)
        {
            int size;
            MPI_Recv(&size, 1, MPI_INT, MASTER, 0, MPI_COMM_WORLD, NULL);

            if (size == -1)
                break;

            while (true)
            {
                // aici primesc bucati de maxim 20 de linii dintr-un anumit paragraf
                int index;
                MPI_Recv(&index, 1, MPI_INT, MASTER, 0, MPI_COMM_WORLD, NULL);

                char *recv = (char *)malloc((size + 1) * sizeof(char));
                MPI_Recv(recv, size, MPI_CHAR, MASTER, 0, MPI_COMM_WORLD, NULL);
                recv[size] = '\0';

                TParagraph p;
                p.done = false;
                p.index = (int *)malloc(sizeof(int));
                (*p.index) = index;
                p.genre = genre;
                p.paragraph = recv;

                status = pthread_mutex_lock(&first_editor_mutex);

                // introduc paragraful needitat intr-o coada de paragrafe
                unedited_pars.push(p);

                status = pthread_mutex_unlock(&first_editor_mutex);

                MPI_Recv(&size, 1, MPI_INT, MASTER, 0, MPI_COMM_WORLD, NULL);
                if (size == 0)
                    break;
            }
        }

        // semnalez terminarea paragrafelor de la master
        TParagraph p;
        p.done = true;

        status = pthread_mutex_lock(&first_editor_mutex);

        unedited_pars.push(p);

        status = pthread_mutex_unlock(&first_editor_mutex);

        // astept terminarea thread-urilor
        for (int i = 0; i < no_threads - 1; ++i)
        {
            pthread_join(editing_threads[i], NULL);
        }

        // trimit paragrafele inapoi la master, alaturi de indexul asociat fiecarui paragraf
        while(!edited_pars.empty()) {
            TParagraph p;
            p = edited_pars.front();
            edited_pars.pop();

            int size = strlen(p.paragraph);
            MPI_Send(&size, 1, MPI_INT, 0, 0, MPI_COMM_WORLD);
            MPI_Send(p.index, 1, MPI_INT, 0, 0, MPI_COMM_WORLD);
            MPI_Send(p.paragraph, size, MPI_CHAR, 0, 0, MPI_COMM_WORLD);
        }

        // semnalez ca am terminat de trimis
        int done = 0;
        MPI_Send(&done, 1, MPI_INT, 0, 0, MPI_COMM_WORLD);
    }
    else
    {
        // aleg functia de editare in functie de rangul workerului
        edit_function _edit = edit_functions[worker_rank - 1];

        // astept in bucla infinita sa fie introduse in coada paragrafe needitate
        while (true)
        {
            status = pthread_mutex_lock(&first_editor_mutex);

            if (unedited_pars.size() != 0)
            {
                TParagraph p;
                // iau primul paragraf din coada
                p = unedited_pars.front();

                // verific daca paragraful din coada semnaleaza sfarsitul editarii
                if (p.done)
                {
                    status = pthread_mutex_unlock(&first_editor_mutex);

                    break;
                }

                unedited_pars.pop();
                status = pthread_mutex_unlock(&first_editor_mutex);

                // editez noul paragraf si il pun in coada cu paragrafele editate
                char *new_p = (char *)malloc((strlen(p.paragraph) + 1) * sizeof(char));
                strcpy(new_p, p.paragraph);
                new_p[strlen(p.paragraph)] = '\0';
                char *edited = _edit(new_p, strlen(new_p));
                p.done = true;
                p.paragraph = edited;

                status = pthread_mutex_lock(&second_editor_mutex);

                edited_pars.push(p);

                status = pthread_mutex_unlock(&second_editor_mutex);
            }
            else
                status = pthread_mutex_unlock(&first_editor_mutex);
        }
    }

    pthread_exit(NULL);
}

int main(int argc, char **argv)
{
    int no_mpi_procs, rank, provided;

    MPI_Init_thread(&argc, &argv, MPI_THREAD_MULTIPLE, &provided);
    MPI_Comm_size(MPI_COMM_WORLD, &no_mpi_procs);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);

    if (no_mpi_procs != NO_WORKERS || argc != 2)
        exit(-1);

    // numarul de thread-uri de pe masina locala
    no_threads = sysconf(_SC_NPROCESSORS_CONF);

    // daca workerul este master
    if (rank == MASTER)
    {
        // iau numele fisierului de input
        char *input_filename = argv[1];
        pthread_t reader_threads[NO_READER_THREADS];
        TReaderArgs **reader_args = (TReaderArgs **)malloc(NO_READER_THREADS * sizeof(TReaderArgs *));

        // pornesc thread-urile
        for (int i = 0; i < NO_READER_THREADS; ++i)
        {
            reader_args[i] = (TReaderArgs *)malloc(sizeof(TReaderArgs));
            reader_args[i]->thread_id = i;
            reader_args[i]->input_filename = input_filename;

            int status = pthread_create(&reader_threads[i], NULL, _reader_thread, reader_args[i]);
        }

        // astept terminarea thread-urilor
        for (int i = 0; i < NO_READER_THREADS; ++i)
        {
            int status = pthread_join(reader_threads[i], NULL);
        }

        // eliberez memoria asociata argumentelor
        for (int i = 0; i < NO_READER_THREADS; ++i)
        {
            free(reader_args[i]);
        }
        free(reader_args);

        // concatenez si refac inputul luand paragrafele din fiecare tip de coada, pentru fiecare gen
        int no_pars = paragraphs[0]->size() + paragraphs[1]->size() + paragraphs[2]->size() + paragraphs[3]->size();
        char *pars[2 * no_pars];

        // aceste paragrafe sunt asezate in ordinea indexului asignat la citire pentru a reface textul
        for (int j = 0; j < 4; ++j)
        {
            for (int i = 0; i < paragraphs[j]->size(); ++i)
            {
                TParagraph p = paragraphs[j]->at(i);
                p.genre.append("\n\0");
                pars[2 * (*p.index)] = (char *)malloc((p.genre.size() + 1) * sizeof(char));
                p.genre.copy(pars[2 * (*p.index)], p.genre.size(), 0);
                pars[2 * (*p.index)][p.genre.size()] = '\0';
                pars[2 * (*p.index) + 1] = p.paragraph;
            }
        }

        // scriu rezultatul in fisier
        string output_filename;
        char *s = strtok(input_filename, ".");
        output_filename += ".";
        output_filename.append(s);
        output_filename += '.';
        output_filename.append("out");
        ofstream output_file(output_filename.c_str());

        for (int i = 0; i < no_pars; i++)
        {
            output_file << pars[2 * i]
                        << pars[2 * i + 1] << '\n';
        }

        output_file.close();
    }
    else
    {
        // initializare mutex
        pthread_mutex_init(&first_editor_mutex, NULL);
        pthread_mutex_init(&second_editor_mutex, NULL);

        // pornesc thread-ul de comunicare cu master
        int rank_recv = 0;
        pthread_t recv_thread;
        pthread_create(&recv_thread, NULL, _editor_thread, &rank_recv);

        // astept terminarea thread-ului de comunicare
        pthread_join(recv_thread, NULL);

        pthread_mutex_destroy(&first_editor_mutex);
        pthread_mutex_destroy(&second_editor_mutex);
    }

    MPI_Finalize();
}