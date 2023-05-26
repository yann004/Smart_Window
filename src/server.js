const express = require('express');
const { Pool } = require('pg');

const app = express();
const port = 8080;

// Paramètres de connexion à la base de données PostgreSQL
const pool = new Pool({
  user: 'postgres',
  host: 'localhost',
  database: 'Smart_Window',
  password: 'admin',
  port: 5432,
});

app.get('/api/data', (req, res) => {
  const { temperature, intensite_pluie, etat_fenetre } = req.query;

  // Insérer les données dans la table donnees_capteurs
  const query = 'INSERT INTO donnees_capteurs (temperature, intensite_pluie, etat_fenetre) VALUES ($1, $2, $3)';
  const values = [temperature, intensite_pluie, etat_fenetre];
  pool.query(query, values, (err, result) => {
    if (err) {
      console.error('Erreur lors de l\'enregistrement des données :', err);
      res.status(500).send('Erreur lors de l\'enregistrement des données');
    } else {
      console.log('Données enregistrées avec succès !');
      res.status(200).send('Données enregistrées avec succès');
    }
  });
});

app.listen(port, () => {
  console.log(`Serveur en écoute sur http://localhost:${port}`);
});
