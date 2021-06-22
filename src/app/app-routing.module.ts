import { NgModule } from "@angular/core";
import { RouterModule, Routes } from "@angular/router";

import { Wasm3dCubeComponent } from "./wasm/3d-cube/3d-cube.component";

const routes: Routes = [{ path: "", component: Wasm3dCubeComponent, data: { demo: true, name: "3D cube" } }];

@NgModule({
  imports: [RouterModule.forRoot(routes, { relativeLinkResolution: "legacy" })],
  exports: [RouterModule],
})
export class AppRoutingModule {}
