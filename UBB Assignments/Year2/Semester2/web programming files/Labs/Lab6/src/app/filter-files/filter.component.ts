import { Component, Input, OnInit } from '@angular/core';
import { HttpClient, HttpHeaders, HttpParams } from '@angular/common/http';
import { map } from 'rxjs/internal/operators/map';
import { File } from '../files';

@Component({
  selector: 'app-filter',
  templateUrl: './filter.component.html',
  styleUrls: ['./filter.component.css']
})

export class FilterComponent implements OnInit{
  @Input() filter!: string;
  files!: File[];

  constructor(private http: HttpClient) { }

  filterTitles(value: string){
    console.log(value);
    const url = 'http://localhost:1234/multimedia.php';
    const data = {action: 'filterTitles', filter: value};
    console.log(data);
    const httpOptions = {
      headers: new HttpHeaders({
        'Content-Type':  'application/json',
        Authorization: 'my-auth-token'
      })
    };

    const req = this.http.post<File[]>(url, JSON.stringify(data), httpOptions);
    req.subscribe((response: File[]) => {
      console.log( response);
      this.files = response;
    }, (error) => {
      console.error(error);
    });
  }

  ngOnInit() {
  }
}
