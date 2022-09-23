-- Infos zum Diebstahl nachschauen. Bei der gegeben Zeit und Ort.
SELECT description 
    FROM crime_scene_reports 
    WHERE year = 2021 
        AND month = 7 
        AND day = 28 
        AND street = 'Humphrey Street';

-- Namen der zeugen finden
SELECT name, transcript 
    FROM interviews 
    WHERE year = 2021 
        AND month = 7 
        AND day = 28;

-- Gucken ob es mehrere gibt
SELECT name 
    FROM people 
    WHERE name = 'Eugene';

-- Drei zeugen gefunden, einer erwähnt am 28. July. 2021 "Bäcker"
SELECT name, transcript
    FROM interviews
    WHERE year = 2021
        AND month = 7
        AND day = 28
        AND transcript LIKE '%bakery%'
    ORDER BY name;
 -- Zeugen: Eugene, Raymond und Ruth

-- Gucken wer transaktionen gemacht hat
SELECT account_number, amount
    FROM atm_transactions
    WHERE year = 2021
        AND month = 7
        AND day = 28
        AND atm_location = 'Leggett Street'
        AND transaction_type = 'withdraw';

-- Namen finden die zu den kontonummern stimmen. Und zu Suspect List hinzufügen.
SELECT name, atm_transactions.amount
    FROM people
    JOIN bank_accounts
        ON people.id = bank_accounts.person_id
    JOIN atm_transactions
        ON bank_accounts.account_number = atm_transactions.account_number
    WHERE atm_transactions.year = 2021
        AND atm_transactions.month = 7
        AND atm_transactions.day = 28
        AND atm_transactions.atm_location = 'Leggett Street'
        AND atm_transactions.transaction_type = 'withdraw';

-- Raymond hört ein gespräch wo es um ein Ticket für den frühsten Flug am July 29, 2021 geht.
-- Den landeort finden würde bedeuten den Fluchtort zu finden
SELECT abbreviation, full_name, city
    FROM airports
    WHERE city = 'Fiftyville';
 -- Flüge vom 29. July überprüfen und nach Zeit sortieren
SELECT flights.id, full_name, city, flights.hour, flights.minute
    FROM airports
    JOIN flights
        ON airports.id = flights.destination_airport_id
    WHERE flights.origin_airport_id =
        (SELECT id
            FROM airports
                WHERE city = 'Fiftyville')
        AND flights.year = 2021
        AND flights.month = 7
        AND flights.day = 29
    ORDER BY flights.hour, flights.minute;

-- Der erste flug kommt um 8:20 am LaGuardia Airport in New York City an (id- 36) Das könnte der Fluchtort sein
-- Alle passagiere in die "Suspect list" hinzufügen und nach der Passport nummer sortieren
SELECT passengers.flight_id, name, passengers.passport_number, passengers.seat
    FROM people
    JOIN passengers
        ON people.passport_number = passengers.passport_number
    JOIN flights
        ON passengers.flight_id = flights.id
    WHERE flights.year = 2021
        AND flights.month = 7
        AND flights.day = 29
        AND flights.hour = 8
        AND flights.minute = 20
    ORDER BY passengers.passport_number;

-- Telefon verlauf überprüfen um die Person zu finden die das Ticket gebucht hat.
-- Mögliche Namen der Anrufer herausfinden und in die "Suspect List" tun Sortieren nach anruf dauer
SELECT name, phone_calls.duration
    FROM people
    JOIN phone_calls
        ON people.phone_number = phone_calls.caller
    WHERE phone_calls.year = 2021
        AND phone_calls.month = 7
        AND phone_calls.day = 28
        AND phone_calls.duration <= 60
    ORDER BY phone_calls.duration;

-- Danach den Namen vom entnehmer herausfinden und nach llänge des anrufes Sortieren
SELECT name, phone_calls.duration
    FROM people
    JOIN phone_calls
        ON people.phone_number = phone_calls.receiver
    WHERE phone_calls.year = 2021
        AND phone_calls.month = 7
        AND phone_calls.day = 28
        AND phone_calls.duration <= 60
    ORDER BY phone_calls.duration;

-- Ruth sagte das der Dieb mit einem Bäcker auto weg gefahren sei inerhalb von 10 Minuten. Fahrzeug besitzer anhand der Kennzeichen der Autos die in der Zeitspanne dort lang fuhren ermitteln und auf die "Suspect List" tun.
SELECT name, bakery_security_logs.hour, bakery_security_logs.minute
    FROM people
    JOIN bakery_security_logs
        ON people.license_plate = bakery_security_logs.license_plate
    WHERE bakery_security_logs.year = 2021
        AND bakery_security_logs.month = 7
        AND bakery_security_logs.day = 28
        AND bakery_security_logs.activity = 'exit'
        AND bakery_security_logs.hour = 10
        AND bakery_security_logs.minute >= 15
        AND bakery_security_logs.minute <= 25
    ORDER BY bakery_security_logs.minute;

-- Bruce war es, er kommt in allen listen vor. Er wird nach New York City geflohen sein. Und robin muss der Complize sein, da er der jenige ist der die Tickets gekauft hat.
