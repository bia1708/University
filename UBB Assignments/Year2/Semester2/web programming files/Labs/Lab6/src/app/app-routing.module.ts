import { NgModule } from '@angular/core';
import { RouterModule, Routes } from '@angular/router';
import { MenuComponent } from './menu/menu.component';
import { FileListComponent } from './file-list/file-list.component';
import { FilterComponent } from './filter-files/filter.component';
import { AddComponent } from './add-file/addfile.component';
import { DeleteComponent } from './delete-file/deletefile.component';
import { UpdateComponent } from './update-file/updatefile.component';

const routes: Routes = [
  {path: '', component: FileListComponent},
  {path: 'files/', component: FileListComponent},
  {path : 'files/filter', component: FilterComponent},
  {path: 'files/add', component:AddComponent},
  {path: 'files/remove', component:DeleteComponent},
  {path: 'files/update', component:UpdateComponent},
];

@NgModule({
  imports: [RouterModule.forRoot(routes)],
  exports: [RouterModule]
})
export class AppRoutingModule { }
