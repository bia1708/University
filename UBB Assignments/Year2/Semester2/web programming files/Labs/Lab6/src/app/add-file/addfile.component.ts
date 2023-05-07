import { Component, Input, OnInit } from '@angular/core';
import { HttpClient, HttpHeaders, HttpParams } from '@angular/common/http';
import { FormBuilder, FormControl, FormGroup } from '@angular/forms';
import Swal from 'sweetalert2';
import { ReactiveFormsModule } from '@angular/forms';
import { map } from 'rxjs/internal/operators/map';
import { File } from '../files';

@Component({
  selector: 'app-addfile',
  templateUrl: './addfile.component.html',
  styleUrls: ['./addfile.component.css']
})

export class AddComponent implements OnInit{
  constructor(
    private http: HttpClient,
    private formBuilder: FormBuilder,
    ) { }


  addForm = this.formBuilder.nonNullable.group({
    title: [''],
    file_format: [''],
    path: [''],
    size: [0],
  });

  addFile(){
    const url = 'http://localhost:1234/multimedia.php';
    const data = {action: 'addFile', title: this.addForm.get('title')?.value, file_format: this.addForm.get('file_format')?.value, path: this.addForm.get('path')?.value, size: this.addForm.get('size')?.value};
    const httpOptions = {
      headers: new HttpHeaders({
        'Content-Type':  'application/json',
        Authorization: 'my-auth-token'
      })
    };

    const req = this.http.post<string>(url, JSON.stringify(data), httpOptions);
    req.subscribe((response: string) => {
      console.log(response);
      Swal.fire('File added succesfully!');
      this.addForm.reset();
    }, (error) => {
      console.error(error);
    });
  }

  ngOnInit() {
    // this.filterFiles();
  }
}
