#include <iostream>
#include <fstream>
#include <string>
#include <speechapi_cxx.h>


using namespace std;
using namespace Microsoft::CognitiveServices::Speech;
using namespace Microsoft::CognitiveServices::Speech::Audio;

//classe Pai
class Personagem {

public:
    int vida = 10;
    int mana = 10;
    int ataque = 1;
    string feitico = "";

    // cura vida do personagem
    void curar(int c) {
        vida = vida + c;
    }
    // Retorna para o usuario o status de cada um dos atributos do personagem
    void printarStatus() {
        cout << "Vida:  " << vida << endl;
        cout << "Mana:  " << mana << endl;
        cout << "Ataque:  " << ataque << endl;
        cout << "Habilidade:  " << feitico << endl;

    }

};

class Guerreiro : public Personagem {

public:

    //construtor
    Guerreiro() {
        this->vida = 10;
        this->mana = 10;
        this->ataque = 1;
        this->feitico = "Malhar.";

    }
    // Habilidade de malhar. Quando utilizada o Guerreiro ir� perder 4 de mana e ganhar 3 de ataque. Atualiza as vari�veis de ataque e mana
    void malhar() {
        ataque += 3;
        mana -= 4;
    }

};

    class Ladino : public Personagem {
    protected:
        bool invisivel = false;

    public:
        //construtor
        Ladino() {
            this->vida = 10;
            this->mana = 10;
            this->ataque = 3;
            this->feitico = "Invisivel.";

        }
        void ficaInivisivel() {
            invisivel = true;
            mana -= 2;
        }

    };


    class Monstro : public Personagem {
    public:
        //construtor
        Monstro() {
            this->vida = 10;
            this->ataque = 1;
            this->feitico = "Morder";
        }

        /*void morder(Personagem p){
          ataque = 3;
          p.vida -= ataque;
        }*/

    };

    class Mago : public Personagem {
    public:
        //construtor
        Mago() {
            this->vida = 10;
            this->mana = 10;
            this->ataque = 1;
            this->feitico = "Bola de Fogo.";
        }
        // habilidade de lan�ar bola de fogo
        void lancarBoladeFogo(Monstro m) {
            int dano;
            dano = ataque * 4;
            m.vida -= ataque;
            mana -= -3;
        }
    };


    auto autenticacao = SpeechConfig::FromSubscription("75cbbc234f5b4f219e037022cb4c7a94", "southcentralus"); // DECLARA��O DA AUTENTICA��O DO RECURSO
    auto requisicao_textofala = SpeechSynthesizer::FromConfig(autenticacao); // DECLARA��O DO OBJETO DE REQUISI��O DE TEXTO EM FALA DO RECURSO
    auto audio_config = AudioConfig::FromDefaultMicrophoneInput(); // DECLARA��O DA ENTRADA DO MICROFONE
    auto requisicao_falatexto = SpeechRecognizer::FromConfig(autenticacao, audio_config); // DECLARA��O DO OBJETO DE REQUISI��O DE FALA EM TEXTO DO RECURSO

    // PROCEDIMENTO QUE REQUISITA DA API A TRANSFORMA��O DE UM TEXTO EM FALA
    void texto_em_fala(string Texto)
    {
        cout << Texto + "\n";
        requisicao_textofala->SpeakTextAsync(Texto).get(); // REQUISI��O DA SINTETIZA��O DE TEXTO EM FALA
    }
    // FUN��O QUE REQUISITA DA API O RECONHECIMENTO DE UMA FALA E A TRANSFORMA��O DESSA FALA EM UM TEXTO
    string fala_em_texto() {
        auto resultado = requisicao_falatexto->RecognizeOnceAsync().get(); // REQUISI��O DO RECONHEIMENTO DE FALA EM TEXTO
        cout << resultado->Text + "\n";
        return resultado->Text; //CONVERS�O DO RESULTADO DO RECONHECIMENTO EM TEXTO
    }

    int main()
    {

        //  AUTENTICA��O DO RECURSO COM A CHAVE E REGI�O INFORMADOS PELO USU�RIO 
        autenticacao->SetSpeechRecognitionLanguage("pt-BR");                //  CONFIGURA��O DA AUTENTICA��O PARA O RECONHECIMENTO DE FALA EM PORTUGU�S 
        autenticacao->SetSpeechSynthesisLanguage("pt-BR");                  //  CONFIGURA��O DA AUTENTICA��O PARA A SINTETIZA��O DE FALA EM PORTUGU�S 
        autenticacao->SetSpeechSynthesisVoiceName("pt-BR-HeloisaRUS"); //pt-BR-Daniel  // CONFIGURA��O DA AUTENTICA��O COM UMA VOZ ESPEC�FICA 
        requisicao_textofala = SpeechSynthesizer::FromConfig(autenticacao); //  REDEFINI��O DO OBJETO REQUISICAO_TEXTOFALA COM AS NOVAS CONFIGURA��ES 
        requisicao_falatexto = SpeechRecognizer::FromConfig(autenticacao, audio_config); //  REDEFINI��O DO OBJETO REQUISICAO_FALATEXTO COM AS NOVAS CONFIGURA��ES

        bool vivo = true; //controla a vida do personagem
        bool reconhece = false; // controla se a IA reconheceu a fala    
        bool mVivo = true; // controla a vida do monstro

        Monstro mo; // objeto da classe Monstro

        texto_em_fala("Bem vindo! Meu nome eh Illus, vou te guiar nessa jornada.");
        texto_em_fala("Caso eu repita algo, eh que nao entendi, por favor diga com mais clareza");
        texto_em_fala("Em um belo dia, se ve em uma caverna escura e encontra um papel escrito:");
        texto_em_fala("Escolha seu destino: Mago, Guerreiro, ou Ladino");

        //repete a fala enquanto nao for reconhecido o comando corretamente
        while (reconhece == false) {


            texto_em_fala("Diga em voz alta sua escolha");

            string opcao = fala_em_texto(); // recebe a op��o do usu�rio em fala e converte em texto

            if (opcao == "Ladino.") {
                Ladino ld;
                reconhece = true; //caso a condi��o seja satisfeita, seta o valor da variavel para true para que nao repita

                texto_em_fala("Aparece um monstro na sua frente, e necessario enfrenta-lo para que saia da caverna.");
                texto_em_fala("O monstro te atacou. Seu personagem tem os seguintes atributos");

                ld.printarStatus(); //retorna o status do personagem Guerreiro

                while (vivo == true) { //enquanto o personagem ainda esteja vivo podera tomar decisoes
                        //o monstro ataca o Ladino;
                    ld.vida -= mo.ataque;

                    //verifica se o monstro esta vivo
                    if (mo.vida <= 0) {
                        mVivo = false;
                    }

                    if (mVivo == true) // caso o monstro esteja vivo, sera possivel ataca-lo
                    {
                        texto_em_fala("Deseja atacar ou usar sua habilidade?");
                        string dec = fala_em_texto();

                        if (dec == "Atacar.")
                        {

                            //o monstro ataca o Ladino;
                            mo.vida -= ld.ataque;
                            texto_em_fala("Monstro atacado.");
                            //o monstro ataca o Ladino;
                            ld.vida -= mo.ataque;
                            ld.printarStatus();

                            cout << "Status do monstro" << endl;
                            mo.printarStatus();
                        }
                        else if (dec == "Habilidade.")
                        {
                            ld.ficaInivisivel();
                            texto_em_fala("Voce nao sofreu dano");
                            cout << "Seu status" << endl;
                            ld.printarStatus();
                            cout << endl;
                            cout << "Status do monstro" << endl;
                            mo.printarStatus();

                        }
                    }
                    else {
                        texto_em_fala("O monstro foi derrotado. Parabens, voce ganhou o jogo");
                    }



                }
            }
            else if (opcao == "Guerreiro.")
            {
                Guerreiro ge;
                reconhece = true;

                texto_em_fala("Aparece um monstro na sua frente, e necessario enfrenta-lo para que saia da caverna.");
                texto_em_fala("O monstro te atacou. Seu personagem tem os seguintes atributos");

                ge.printarStatus(); //retorna o status do personagem Guerreiro

                while (vivo == true) { //enquanto o personagem ainda esteja vivo podera tomar decisoes
                    ge.vida -= mo.ataque;

                    //verifica se o monstro esta vivo
                    if (mo.vida <= 0) {
                        mVivo = false;
                    }
                    if (mVivo == true) // caso o monstro esteja vivo, sera possivel ataca-lo
                    {
                        texto_em_fala("Deseja atacar ou usar sua habilidade?");
                        string dec = fala_em_texto();

                        if (dec == "Atacar.")
                        {
                            mo.vida -= ge.ataque;
                            texto_em_fala("Monstro atacado.");
                            ge.vida -= mo.ataque;
                            ge.printarStatus();
                            cout << endl;
                            cout << "Status do monstro" << endl;
                            mo.printarStatus();
                        }
                        else if (dec == "Habilidade.")
                        {
                            ge.malhar();
                            mo.vida -= 2;
                            ge.vida -= 3;
                            texto_em_fala("O monstro te mordeu. Agora, voce tem os seguintes atributos");
                            ge.printarStatus();
                            cout << endl;
                            cout << "Status do monstro" << endl;
                            mo.printarStatus();

                        }
                    }
                    else {
                        texto_em_fala("O monstro foi derrotado. Parabens, voce ganhou o jogo");
                    }
                }
            }
            else if (opcao == "Mago.") {
                        Mago mg;
                        reconhece = true;

                        //verifica se o monstro esta vivo
                        if (mo.vida <= 0) {
                            mVivo = false;
                        }

                        if (mVivo == true) // caso o monstro esteja vivo, sera possivel ataca-lo
                        {
                            texto_em_fala("Deseja atacar ou usar sua habilidade?");
                            string dec = fala_em_texto();

                            if (dec == "Atacar.")
                            {
                                //o mago ataca o monstro
                                mo.vida -= mg.ataque;
                                texto_em_fala("Monstro atacado.");
                                //o monstro ataca o Mago;
                                mg.vida -= mo.ataque;
                                mg.printarStatus();
                                cout << endl;
                                cout << "Status do monstro" << endl;
                                mo.printarStatus();
                            }
                            else if (dec == "Habilidade.")
                            {
                                mg.lancarBoladeFogo(mo);
                                texto_em_fala("O monstro te mordeu. Agora, voce tem os seguintes atributos");
                                mg.printarStatus();
                                cout << endl;

                                cout << "Status do monstro" << endl;
                                mo.printarStatus();

                            }
                        }
                        else {
                            texto_em_fala("O monstro foi derrotado. Parabens, voce ganhou o jogo");
                        }


                    }
                }
                return 0;
    }
            
            
        