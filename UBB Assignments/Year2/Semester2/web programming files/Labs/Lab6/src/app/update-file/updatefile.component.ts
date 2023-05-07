import { Component, Input, OnInit } from '@angular/core';
import { HttpClient, HttpHeaders, HttpParams } from '@angular/common/http';
import { FormBuilder, FormControl, FormGroup } from '@angular/forms';
import Swal from 'sweetalert2';
import { ReactiveFormsModule } from '@angular/forms';
import { map } from 'rxjs/internal/operators/map';
import { File } from '../files';

@Component({
  selector: 'app-updatefile',
  templateUrl: './updatefile.component.html',
  styleUrls: ['./updatefile.component.css']
})

export class UpdateComponent implements OnInit{
  constructor(
    private http: HttpClient,
    private formBuilder: FormBuilder,
    ) { }


  updateForm = this.formBuilder.nonNullable.group({
    title: [''],
    file_format: [''],
    path: [''],
    size: [0],
  });

  updateFile(){
    const url = 'http://localhost:1234/multimedia.php';
    const data = {action: 'updateFile', title: this.updateForm.get('title')?.value, file_format: this.updateForm.get('file_format')?.value, path: this.updateForm.get('path')?.value, size: this.updateForm.get('size')?.value};
    const httpOptions = {
      headers: new HttpHeaders({
        'Content-Type':  'application/json',
        Authorization: 'my-auth-token'
      })
    };

    const req = this.http.post<string>(url, JSON.stringify(data), httpOptions);
    req.subscribe((response: string) => {
      console.log(response);
      Swal.fire('File updated succesfully!');
      this.updateForm.reset();
    }, (error) => {
      console.error(error);
    });
  }

  ngOnInit() {
  }
}
