import * as Three from "three";
import {Wireframe} from "three/examples/jsm/Addons.js";
import { color } from "three/tsl";
import {OrbitControls} from "three/examples/jsm/Addons.js";

const sc = Three.scene()

const camera = new Three.PerspectiveCmaera(75, window.innerWidth/window.innerHeight, .1, 1000)

const renderer = new Three.WebGLRenderer(
{
	canvas : document.querySelector("#bg"),
});

renderer.setSize(window.innerWidth, window.innerHeight)
renderer.setPixelRatio(window.devicePixelRatio)

camera.position.z = 30;

//renderer.render(sc, camera);

const geometry = new Three.TorusGeometry(10, 3, 16, 100);

const material = new Three.MeshBasicmaterial(
	{
		color: 0x1fffffff,
		wireframe:true
	}
);

const torusMesh = new Three.Mesh(geometry, material);

const pointLight = new Three.PointLIght(0xffffff);

const ambientLight = new Three.AmbientLight(0xffffff);

pointLight.position.set(5,3,5);

scene.add(torusMesh);

//renderer.render(sc, camera);

function animate(){
	requestAnimationFrame(animate);
	renderer.render(scene, camera);
}

animation();