#ifndef CLSCADENA_H_INCLUDED
#define CLSCADENA_H_INCLUDED
///CLASE CADENA
///-------------------------------------------------------///
class Cadena{
private:
    char *palabra;
    int tam;
public:
    //constructor

    Cadena(){
        tam=5;
        palabra=new char[tam];
        if(palabra==NULL){
            cout<<"ERROR DE ASIGNACION DE MEMORIA";
            return;
        }
        strcpy(palabra,"0000");
    }

    //metodos
    void Mostrar(){
        cout<<palabra;
    }
    //destructor
    ~Cadena(){
        delete palabra;
    }
    //gets
    const char *getPalabra(){return palabra;}
    int getTam(){return tam;}
    //sets
    void setPalabra(const char *algo){
            int tamNuevo=strlen(algo)+1;
            if(tam==tamNuevo){
                strcpy(palabra,algo);
            }
            else{
                delete palabra;
                tam=tamNuevo;
                palabra=new char[tam];
                if(palabra==NULL){
                    cout<<"ERROR DE ASIGNACION DE MEMORIA";
                    return;
                }
                strcpy(palabra,algo);
            }
    }

    void Concatenar(const char *agregar){
        char *aux;
        int tamanio=tam+strlen(agregar);
        aux=new char[tamanio];
        if(aux==NULL)return;
        strcpy(aux,palabra);
        strcpy(&aux[tam-1], agregar);
        cout<<aux<<endl;
        system("pause");
        delete palabra;
        tam=tamanio;
        palabra=new char[tamanio];
        if(palabra==NULL) return;
        strcpy(palabra,aux);
        delete aux;
    }

    bool operator==(Cadena aux){
        if(strcmp(palabra,aux.palabra)==0) return true;
        return false;
    }
    bool operator==(int tamNuevo){
        if(tam==tamNuevo) return true;
        return false;
    }
    bool operator>(Cadena aux){
        if(strlen(palabra)>strlen(aux.palabra)){return true;}
        else{
            return false;
        }
    }
    bool operator>(const char *cad){
        if(strlen(palabra)>strlen(cad)){return true;}
        else{
            return false;
        }
    }
    bool operator<=(Cadena aux){
        if(strlen(palabra)<=strlen(aux.palabra)){return true;}
        else{
            return false;
        }
    }
    bool operator=(Cadena aux){
        strcpy(palabra,aux.palabra);
        return true;
    }
      bool operator=(const char *aux){
        strcpy(palabra,aux);
        return true;
    }
};



///-------------------------------------------------------///
#endif // CLSCADENA_H_INCLUDED
