import { Component, OnInit } from '@angular/core';
import { HttpClient, HttpHeaders, HttpParams } from '@angular/common/http';
import { map } from 'rxjs/internal/operators/map';
import { File } from '../files';

@Component({
  selector: 'app-list',
  templateUrl: './file-list.component.html',
  styleUrls: ['./file-list.component.css']
})

export class FileListComponent implements OnInit{
  files!: File[];

  constructor(private http: HttpClient) { }

  getFileList() {
    const url = 'http://localhost:1234/multimedia.php';
    const data = {action: 'getTitles'};
    const httpOptions = {
      headers: new HttpHeaders({
        'Content-Type':  'application/json',
        Authorization: 'my-auth-token'
      })
    };

    const req = this.http.post<File[]>(url, JSON.stringify(data), httpOptions);
    req.subscribe((response: File[]) => {
      this.files = response;
    }, (error) => {
      console.error(error);
    });
  }

  ngOnInit() {
    this.getFileList();
  }
}
