import { Injectable } from '@angular/core';
import { HttpClient, HttpHeaders } from '@angular/common/http';
import { environment } from 'src/environments/environment';
import { Observable } from 'rxjs/internal/Observable';

@Injectable({
    providedIn: 'root'
})
export class Service
{
    readonly baseUrl = environment.baseUrl;

    
    constructor (private http: HttpClient){
      
    }

    getPictura(id_categorie: string):Observable<any>{
        return this.http.get(this.baseUrl+'values/'+ id_categorie); //controler din bck
    }

    getUser( username: string, parola: string, mail: string):Observable<any>{

        let headers = new HttpHeaders();
        headers  = headers.append('responseType', 'json');
        return this.http.get<number>(this.baseUrl + `values/${username}/${parola}/${mail}`, {headers: headers});
    }

    postLikes( id_user:number, id_pictura:number, id_categorie: number):Observable<any>{

        let headers = new HttpHeaders();
        headers  = headers.append('responseType', 'json');
        return this.http.post(this.baseUrl + `values/${id_user}/${id_pictura}/${id_categorie}`, {headers: headers});
    }


}