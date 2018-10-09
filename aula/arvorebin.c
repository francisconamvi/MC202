int arvore_vazia(No *arvore){
    if(arvore==NULL)
        return 1;
    else
        return 0;
}

int verifica_elemento(No *arvore, int ele){
    if(arvore->ele == ele)
        return 1;
    else{
        if(arvore->fe == NULL)
            return 0;
        else if(arvore->)
        esq = verifica_elemento(arvore->fe, ele);
        dir = verifica_elemento(arvore->fd, ele);
        if(esq || dir)
            return 1;
    }
}

int numero_folhas(No *p){
    if (p == NULL)
        return 0;
    else
        if ()
}

No *Liberar(No *p){
    if(p != NULL){
        p->e = Liberar(p->e);
        p->d = Liberar(p->d);
        free(p);
    }
    return NULL;
}

int Iguais(No *p, No *q){
    if(p == NULL && q == NULL)
        return 1;
    if(p == NULL || q == NULL)
        return 0;
    if(p->info == q->info)
        return Iguais(p->esq) && Iguais(p->dir)
    else
        return 0;
    
}
