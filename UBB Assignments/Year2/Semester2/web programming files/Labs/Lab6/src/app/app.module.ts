import { NgModule } from '@angular/core';
import { BrowserModule } from '@angular/platform-browser';
import { HttpClientModule } from '@angular/common/http';

import { AppRoutingModule } from './app-routing.module';
import { AppComponent } from './app.component';
import { FileListComponent } from './file-list/file-list.component';
import { RouterModule } from '@angular/router';
import { MenuComponent } from './menu/menu.component';
import { FilterComponent } from './filter-files/filter.component';
import { AddComponent } from './add-file/addfile.component';
import { ProfileEditorComponent } from './profile-editor/profile-editor.component';
import { ReactiveFormsModule } from '@angular/forms';
import { DeleteComponent } from './delete-file/deletefile.component';
import { UpdateComponent } from './update-file/updatefile.component';

@NgModule({
  declarations: [
    AppComponent,
    FileListComponent,
    MenuComponent,
    FilterComponent,
    AddComponent,
    DeleteComponent,
    UpdateComponent,
    ProfileEditorComponent,
  ],
  imports: [
    BrowserModule,
    AppRoutingModule,
    HttpClientModule,
    ReactiveFormsModule,
    RouterModule.forRoot([
      { path: '', component: AppComponent },
    ])
  ],
  providers: [],
  bootstrap: [AppComponent]
})
export class AppModule { }
