import { Component, Input, OnInit } from '@angular/core';
import { HttpClient, HttpHeaders, HttpParams } from '@angular/common/http';
import { FormBuilder, FormControl, FormGroup } from '@angular/forms';
import Swal from 'sweetalert2';
import { ReactiveFormsModule } from '@angular/forms';
import { map } from 'rxjs/internal/operators/map';
import { File } from '../files';

@Component({
  selector: 'app-deletefile',
  templateUrl: './deletefile.component.html',
  styleUrls: ['./deletefile.component.css']
})

export class DeleteComponent implements OnInit{
  constructor(
    private http: HttpClient,
    private formBuilder: FormBuilder,
    ) { }

  deleteForm = this.formBuilder.nonNullable.group({
    title: [''],
  });

  deleteFile(){
    const url = 'http://localhost:1234/multimedia.php';
    const data = {action: 'removeFile', title: this.deleteForm.get('title')?.value};
    const httpOptions = {
      headers: new HttpHeaders({
        'Content-Type':  'application/json',
        Authorization: 'my-auth-token'
      })
    };

    const req = this.http.post<string>(url, JSON.stringify(data), httpOptions);
    req.subscribe((response: string) => {
      console.log(response);
      Swal.fire('File(s) removed successfully!');
      this.deleteForm.reset();
    }, (error) => {
      console.error(error);
    });
  }

  ngOnInit() {
  }
}
