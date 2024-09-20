// import { useState } from 'react'
import { BrowserRouter as Router, Route, Routes } from "react-router-dom";
import "./App.css";

import NavBar from "./components/NavBar";
import MainMenu from "./pages/MainMenu";
import Department from "./pages/department";
import CreateUser from "./pages/CreateUser";
import DisplayData from "./components/DisplayData";

function App() {
  // const [count, setCount] = useState(0)

  return (
    <>
      <NavBar />
      <Router>
        <Routes>
          <Route path="/" element={<MainMenu />} />
          <Route path="/new" element={<CreateUser />} />
          <Route path="/user/:id" element={<DisplayData />} />
          <Route path="/department/:dept" element={<Department />} />
        </Routes>
      </Router>
    </>
  );
}

export default App;
