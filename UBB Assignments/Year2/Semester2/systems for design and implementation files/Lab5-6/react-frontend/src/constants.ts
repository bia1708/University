const PROD_BACKEND_API_URL = "http://127.0.0.1:8000/"; //"http://16.16.75.254/";
const DEV_BACKEND_API_URL = "http://127.0.0.1:8000/";

export const BACKEND_API_URL =
	process.env.NODE_ENV === "development" ? DEV_BACKEND_API_URL : PROD_BACKEND_API_URL;