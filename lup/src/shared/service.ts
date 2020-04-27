import { Injectable } from '@angular/core';
import { HttpClient } from '@angular/common/http';
import { environment } from 'src/environments/environment';
import { Observable } from 'rxjs/internal/Observable';


@Injectable({
    providedIn: 'root'
})
export class Service
{
    readonly baseUrl = environment.baseUrl;
    constructor (private http: HttpClient){}

    getPictura(id_categorie: string):Observable<any>{
        return this.http.get(this.baseUrl+'values/'+ id_categorie); //controler din bck
    }

}